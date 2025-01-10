import time
class Item:
    def __init__(self, name, description):
        self.name = name
        self.description = description

class Character:
    def __init__(self, name, health, attack, defense, magic):
        self.name = name
        self.health = health
        self.max_health = health
        self.attack = attack
        self.defense = defense
        self.magic = magic
        self.inventory = []

    def attack_target(self, target):
      target.health -= self.attack
      if target.health < 0:
        target.health = 0
      print(f"{self.name} атакует {target.name} и наносит {self.attack} урона.")
    
    def use_magic(self, target, spell):
        if spell == "heal":
           self.health += self.magic
           if self.health > self.max_health:
             self.health = self.max_health
           print(f"{self.name} использует лечение и восстанавливает {self.magic} здоровья.")
        elif spell == "fireball":
             target.health -= self.magic * 0.75
             if target.health < 0:
               target.health = 0
             print(f"{self.name} использует огненный шар и наносит {self.magic * 0.75} урона {target.name}.")
        
class Player(Character):
    def __init__(self, name):
      super().__init__(name, 100, 10, 5, 20)


class Enemy(Character):
  def __init__(self, name, health, attack, defense):
    super().__init__(name, health, attack, defense, 0)

class Location:
    def __init__(self, name, description, objects):
        self.name = name
        self.description = description
        self.objects = objects

class World:
    def __init__(self):
        self.locations = {}
    
    def add_location(self, location):
        self.locations[location.name] = location

    def get_location(self, name):
      return self.locations[name]

def print_slow(text, delay=0.02):
    for char in text:
        print(char, end='', flush=True)
        time.sleep(delay)
    print()


def main():
  world = World()

  forest = Location("forest", "Ты находишься в густом лесу.", ["tree", "chest"])
  cave = Location("cave", "Ты в темной пещере.", ["monster", "torch"])
  
  world.add_location(forest)
  world.add_location(cave)
  
  player = Player("Герой")
  current_location = world.get_location("forest")
  print_slow(f"Ты находишься в {current_location.description}")
  
  
  playing = True

  while playing:
      action = input("> ")
      action = action.lower()

      if action == "help":
        print_slow("Доступные команды: help, look, move, inventory, attack, magic")
      elif action == "look":
        print_slow(f"Ты находишься в {current_location.description}. Ты видишь: {', '.join(current_location.objects)}")
      elif action.startswith("move"):
          parts = action.split()
          if len(parts) > 1:
             direction = parts[1]
             if direction == "cave" and current_location.name != "cave":
                 current_location = world.get_location("cave")
                 print_slow("Вы переместились в пещеру")
             elif direction == "forest" and current_location.name != "forest":
                current_location = world.get_location("forest")
                print_slow("Вы вернулись в лес.")
             else:
                print_slow("Неверное направление.")
          else:
             print_slow("Неверный формат команды. Пример: move forest")
      elif action == "inventory":
          if len(player.inventory) == 0:
            print_slow("Инвентарь пуст.")
          else:
            print_slow("Инвентарь:")
            for item in player.inventory:
              print_slow(f"- {item.name}: {item.description}")
      elif action.startswith("attack"):
           if "monster" in current_location.objects:
             monster = Enemy("Злой монстр", 50, 5, 2)
             print_slow("Вы начали бой с монстром")
             while monster.health > 0:
               player.attack_target(monster)
               print_slow(f"У монстра осталось {monster.health} здоровья")
               if monster.health > 0:
                 monster.attack_target(player)
                 print_slow(f"У тебя осталось {player.health} здоровья")
               if player.health <= 0:
                 print_slow("Ты погиб")
                 playing = False
                 break
             if monster.health == 0:
                print_slow("Монстр повержен!")
                current_location.objects.remove("monster")
                chest = Item("Сундук", "Старый сундук с сокровищами")
                current_location.addObject("chest")
                print_slow("Сундук появился на месте битвы")
           else:
            print_slow("Здесь нет монстров")
      elif action.startswith("magic"):
          parts = action.split()
          if len(parts) > 1:
            spell = parts[1]
            if "monster" in current_location.objects:
                 monster = Enemy("Злой монстр", 50, 5, 2)
                 player.use_magic(monster, spell)
                 print_slow(f"У монстра осталось {monster.health} здоровья")
            else:
                 player.use_magic(player, spell)
          else:
            print_slow("Не указано заклинание. Пример: magic heal")
      elif action == "quit":
        print_slow("Завершение игры")
        playing = False
      elif action == "take":
         parts = action.split()
         if len(parts) > 1:
           item_name = parts[1]
           if item_name in current_location.objects:
              if item_name == "chest":
                 chest = Item("Золото", "Много золота")
                 player.inventory.append(chest)
                 current_location.objects.remove(item_name)
                 print_slow("Ты взял золото из сундука")
              else:
                 item = Item(item_name, "Объект который ты подобрал")
                 player.inventory.append(item)
                 current_location.objects.remove(item_name)
                 print_slow(f"Ты взял {item_name}")
           else:
                print_slow("Нет такого предмета")
         else:
             print_slow("Не указан предмет. Пример: take chest")

      else:
        print_slow("Неизвестная команда")

if __name__ == "__main__":
  main()