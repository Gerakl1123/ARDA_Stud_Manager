import random

# Списки русских имён и фамилий
first_names = [
    "Алексей", "Мария", "Иван", "Анна", "Дмитрий", "Ольга", "Сергей", "Екатерина", 
    "Никита", "Наталья", "Михаил", "Елена", "Артём", "Татьяна", "Максим", "Юлия"
]

last_names = [
    "Иванов", "Петрова", "Сидоров", "Кузнецова", "Смирнов", "Попова", "Васильев", "Морозова", 
    "Новиков", "Фёдорова", "Михайлов", "Борисова", "Сорокин", "Киселёва", "Орлов", "Зайцева"
]

students = []

for i in range(50):
    name = random.choice(first_names)
    surname = random.choice(last_names)
    fullname = f"{name}{surname}"
    
    if i % 2 == 0:
        score = random.randint(0, 5)
    else:
        score = round(random.uniform(0, 5), 2)
    
    students.append(f"{fullname} {score}")

# Сохранение в файл
with open("S.txt", "w", encoding="utf-8") as f:
    f.write("\n".join(students))

print("Файл 'students.txt' создан с 1000 студентами.")
