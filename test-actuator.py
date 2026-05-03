#!/usr/bin/env python3
"""
Script pour tester l'actuateur via des missions TAKE, DROP, IDLE et IDLE_TOP.
"""

import serial
import sys
from typing import Optional

class ActuatorTester:
    # Mission types
    TAKE = 0  # PUT_IN_STOCK
    DROP = 1
    IDLE = 2
    IDLE_TOP = 3
    
    # Mission status (from responses)
    STATUS_NAMES = {
        0: "RUNNING",
        1: "SUCCESS",
        2: "ERROR",
    }
    
    def __init__(self, port: str = "/dev/actuator-front", baudrate: int = 115200):
        """Initialiser la connexion série."""
        self.port = port
        self.baudrate = baudrate
        self.serial = None
        self.mission_id = 1
        
    def connect(self) -> bool:
        """Se connecter au port série."""
        try:
            self.serial = serial.Serial(self.port, self.baudrate, timeout=2)
            print(f"✓ Connecté au port {self.port} à {self.baudrate} baud")
            return True
        except Exception as e:
            print(f"✗ Erreur de connexion: {e}", file=sys.stderr)
            return False
    
    def disconnect(self):
        """Fermer la connexion série."""
        if self.serial:
            self.serial.close()
            print("✓ Déconnecté")
    
    def _send_command(self, command: str) -> Optional[str]:
        """Envoyer une commande et lire la réponse."""
        if not self.serial or not self.serial.is_open:
            print("✗ Non connecté au port série", file=sys.stderr)
            return None
        
        try:
            self.serial.write(command.encode())
            response = self.serial.readline().decode().strip()
            return response if response else None
        except Exception as e:
            print(f"✗ Erreur: {e}", file=sys.stderr)
            return None
    
    def send_mission(self, mission_type: int, should_turn: bool = False, should_keep: bool = False) -> bool:
        """Envoyer une mission."""
        turn_val = 1 if should_turn else 0
        keep_val = 1 if should_keep else 0
        
        command = f"M{self.mission_id};{mission_type};{turn_val};{keep_val}F"
        print(f"→ Envoi: {command}")
        
        response = self._send_command(command)
        if response:
            print(f"← Réponse: {response}")
            self._parse_response(response)
        
        self.mission_id += 1
        return True
    
    def send_take(self, should_turn: bool = False, should_keep: bool = False):
        """Envoyer une mission TAKE (PUT_IN_STOCK)."""
        print("\n📦 Mission TAKE (PUT_IN_STOCK)")
        self.send_mission(self.TAKE, should_turn, should_keep)
    
    def send_drop(self, should_turn: bool = False, should_keep: bool = False):
        """Envoyer une mission DROP."""
        print("\n📤 Mission DROP")
        self.send_mission(self.DROP, should_turn, should_keep)
    
    def send_idle_top(self):
        """Aller à IDLE_TOP."""
        print("\n↑ Commande: Aller à IDLE_TOP")
        self.send_mission(self.IDLE_TOP, False, False)
    
    def send_idle(self):
        """Aller à IDLE."""
        print("\n↓ Commande: Aller à IDLE")
        self.send_mission(self.IDLE, False, False)
    
    def _parse_response(self, response: str):
        """Parser une réponse de mission."""
        if response.startswith("A") and response.endswith("F"):
            try:
                parts = response[1:-1].split(";")
                if len(parts) == 2:
                    mission_id = int(parts[0])
                    status = int(parts[1])
                    status_name = self.STATUS_NAMES.get(status, "UNKNOWN")
                    print(f"  → Mission {mission_id}: {status_name}")
            except ValueError:
                pass
    
    def interactive_menu(self):
        """Menu interactif."""
        print("\n" + "="*50)
        print("  TESTEUR D'ACTUATEUR")
        print("="*50)
        
        while True:
            print("\nCommandes disponibles:")
            print("  1 - TAKE (simple)")
            print("  2 - TAKE + TURN")
            print("  3 - TAKE + KEEP")
            print("  4 - TAKE + TURN + KEEP")
            print("  5 - DROP (simple)")
            print("  6 - DROP + TURN")
            print("  7 - DROP + KEEP")
            print("  8 - DROP + TURN + KEEP")
            print("  9 - Aller à IDLE_TOP")
            print("  10 - Aller à IDLE")
            print("  0 - Quitter")
            print("-"*50)
            
            try:
                choice = input("Choix: ").strip()
                
                if choice == "0":
                    break
                elif choice == "1":
                    self.send_take()
                elif choice == "2":
                    self.send_take(should_turn=True)
                elif choice == "3":
                    self.send_take(should_keep=True)
                elif choice == "4":
                    self.send_take(should_turn=True, should_keep=True)
                elif choice == "5":
                    self.send_drop()
                elif choice == "6":
                    self.send_drop(should_turn=True)
                elif choice == "7":
                    self.send_drop(should_keep=True)
                elif choice == "8":
                    self.send_drop(should_turn=True, should_keep=True)
                elif choice == "9":
                    self.send_idle_top()
                elif choice == "10":
                    self.send_idle()
                else:
                    print("✗ Choix invalide", file=sys.stderr)
            
            except KeyboardInterrupt:
                print("\n✓ Arrêt...")
                break
            except Exception as e:
                print(f"✗ Erreur: {e}", file=sys.stderr)


def main():
    """Fonction principale."""
    tester = ActuatorTester()
    
    if not tester.connect():
        sys.exit(1)
    
    try:
        tester.interactive_menu()
    finally:
        tester.disconnect()


if __name__ == "__main__":
    main()
