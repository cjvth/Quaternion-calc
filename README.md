# Quaternion-calc
Калькулятор кватернионов и комплексных чисел
Эта программа была написана только для НПК, но, если она вдруг кому-то пригодится (я буду удивлён), можете использовать

[Скачать exe](https://github.com/cjvth/Quaternion-calc/releases/download/1.0/Quaternion.calc.exe)

## Инструкция
### Входные данные
Программа поддерживает операции сложения, вичитания, умножения, деления и взятия квадратного корня. Можно использовать скобки для задания приоритета операций. Программа получает на вход строку с выражением и возвращает результат.
Выражения могут быть записаны так же, как и обычные математические выражения, но можно использовать мнимые единицы (*i, j, k*). Квадратный корень записывается как sqrt(...)
Пробелы ни на что не влияют.
Примеры корректных выражений:
[li] 
* sqrt(3 + 4i)
* (7 + 45i +13j) / (1-7j + 5.8k +   i)
* 5* (3i-k)
* (1.8 + i)(i+1)

### Выходные данные
Выводится строка, в которой записан кватернион. Например, 0.000000 + 0.000000i + 0.000000j + 0.000000k
### Пользовательский интерфейс
Программа представляет собой командную строку. В неё можно вводить следующие команды:
[li]
* Корректное выражение кватерниона -> посчитать и вывести результат
* r -> прочитать выражение из файла input.txt
* s -> сохранить последний результат в output.txt
* , -> если в вашей системе разделитель десятичной и целой части числа является запятой, то в программе разделитель тоже быдет запятой
* . -> вернуть вместо разделителя точку
* q -> выйти из программы
