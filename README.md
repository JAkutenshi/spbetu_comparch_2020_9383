# Архитектура  ЭВМ (группа 9383)

## Таблица текущего состояния сдачи работ

| ##   | ФИО                   | Github                   | lab1  | lab2  | lab3  | lab4  | lab5  | lab6  | lab7  | lab8  | Итог |
| ---- | --------------------- | ------------------------ | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ---- |
| 1    | Арутюнян Самвел       | sttie                    | 01.10 | 15.10 |       |       |       |       |       |       |      |
| 2    | Гладких Адрей         | FollowJust               | 24.09 | 08.10 |       |       | 26.11 |       |       |       |      |
| 3    | Гордон Дмитрий        | Ciratoku                 |       |       |       |       |       |       |       |       |      |
| 4    | Камзолов Никита       | KamzolovNikita           | 24.09 | 08.10 |       |       | 19.11 |       |       |       |      |
| 5    | Карпекина Анна        | Anny45                   | 08.10 | 15.10 |       | 19.11 | 26.11 |       |       |       |      |
| 6    | Корсунов Антон        | emptyfs                  | 15.10 |       |       | 19.11 |       |       |       |       |      |
| 7    | Крейсманн Кирилл      | kirill-1103              | 24.09 | 08.10 | 22.10 |       |       |       |       |       |      |
| 8    | Лапина Анастасия      | Anastasialapina          | 01.10 | 15.10 |       |       |       |       |       |       |      |
| 9    | Лихашва Анастасия     | NastyaLihashva           |       | 26.11 |       |       |       |       |       |       |      |
| 10   | Лысова Александра     | AlexandraLysova          | 01.10 | 15.10 | 22.10 |       |       |       |       |       |      |
| 11   | Моисейченко Кирилл    | Kirill-Mois              | 08.10 |       |       |       |       |       |       |       |      |
| 12   | Никифоров Павел       |                          |       |       |       |       |       |       |       |       |      |
| 13   | Ноздрин Василий       | BasilNozdrin             | 15.10 |       |       |       |       |       |       |       |      |
| 14   | Орлов Даниил          | heesus                   |       |       |       |       |       |       |       |       |      |
| 15   | Пономаренко Софья     | sfpmrnk                  |       | 19.11 |       |       |       |       |       |       |      |
| 16   | Поплавский Иван       | didges                   | 01.10 | 22.10 |       |       |       | 19.11 |       |       |      |
| 17   | Рыбников Роман        | RomanRybnikov            | 01.10 | 22.10 |       | 19.11 |       |       |       |       |      |
| 18   | Самулевич Василий     |                          |       |       |       |       |       |       |       |       |      |
| 19   | Сергиенкова Анастасия | AnastasiaSergiencova2305 | 01.10 | 22.10 |       |       |       |       |       |       |      |
| 20   | Хотяков Евгений       | Hotiakov                 | 24.09 | 08.10 |       | 19.11 |       |       |       |       |      |
| 21   | Храпова Полина        |                          |       |       |       |       |       |       |       |       |      |
| 22   | Чебесова Ирина        | chebesovairina           | 01.10 | 15.10 |       |       |       |       |       |       |      |
| 23   | Чумак Михаил          | Machumak00               | 24.09 | 22.10 |       |       |       |       |       |       |      |

## Правила работы с репозиторием (прочитайте внимательно!)

 - Для начала работы каждый студент делает форк (fork) репозитория на свой GitHub аккаунт.
Каждый студент работает строго в своей директории firstname/ , где firstname - название директории в соотвтествии с вашей фамилией в таблицей, начинающаяся со строчой буквы. Работа в чужих директориях строго-настрого запрещается.

> Как сделать так, чтобы этого не произошло? Не надо синхронизировать свой репозиторий с master-веткой origin-репозитория. Не надо делать fetch-и с origin-репозитория или тем более fork-ов ваших коллег. Сделали один раз fork -- с ним и работаете, в своей директории. На надо удалять никаких файлов: ни чужих, ни своих с других веток, например. Не надо выполнять merge своих веток лишний раз, ибо это просто излишне. Работаете вы в отдельных ветках для каждой из лабораторных. Все это -- настоятельные советы, которые должны нивелировать возможность конфликтов при работе. Большая просьба их соблюдать, уважая время и труд ваших коллег.

- Для каждой лабораторной требуется создавать отдельную директорию lab#, где # - номер - лабораторной от 1 до 5.  Для курсовой создается директория cw. Пример устройства корневой директории курса:

```
.
├── efremov
│   ├── lab1
│   │   ├── report.pdf
│   │   ├── report.odt
│   │   └── source.asm
│   └── lab2
│   │   ├── report.pdf
│   │   ├── report.odt
│   │   └── source.asm
├── ivanova
│   ├── lab1
│   │   ├── report.pdf
│   │   ├── report.odt
│   │   └── source.asm
│   └── lab2
│   │   ├── report.pdf
│   │   ├── report.odt
│   │   └── source.asm
└── README.md
```

- Внутри должны находиться:
    - Исходный код лабораторных программ;
    - makefile для создания исполняемого модуля (4 и 6 работы);
    - Отчет в формате pdf по шаблону с [сайта университета](https://etu.ru/ru/studentam/dokumenty-dlya-ucheby/). Отчеты, оформленные иначе приниматься не будут. Не тратьте наше общее время.

> На всякий случай, каковы требования к оформлению: 14й шрифт Times New Roman (или похожий, например, свободный шрифты Linux Libertine или Liberation Serif), 1.5 строки интервал, красная строка; заголовки должны иметься для каждого из разделов докумета, имеют такой же 14pt шрифт, выделяются жирным; обязательные разделы: цель работы, ход выполнения, ответы на вопросы (пожалуйста, пишите сами формулировки вопросов перед ответами!), выводы; копирование текста методички в отчет вовсе не требуется; все изображения и листинги должны быть информативные (пример неинформативного скриншота: скриншот всего рабочего стола с открытым FAR-ом посреди какого-то представления исполняемого модуля. Как сделать информативнее: уменьшить размер изображения до тех размеров, в которые помещается ровно тот участок представления, который что-то отображает (например, границу PSP), подчеркнуть, выделить требуемый участок изображения) пронумерованы и подписаны тем же 14pt обычным шрифтом, выровненным по центру (Пример: Рисунок 2 -- Представление сегмента стека в памяти.), на рисунок, раз уж вы его представили, вы где-то должны ссылаться (иначе зачем он нужен вообще?). Страницы нумеруются в нижней части документа, по центру (если используете шаблон с сайта вуза, все уже сделано за вас). Пожалуйста, соблюдайте эти не сложные требования к оформлению: их так гораздо проще как писать (имеется четкая структура, все эти требования по-умолчанию уже есть в вузовском шаблоне), так и проверять.

- Для каждой лабораторной создается отдельная новая ветка (branch) из master-ветви с названием вида < firstname_lab# >, где firstname - фамилия (аналогично названию вашей личной директории), а # - номер работы, тоже со строчной буквы). Пример создания ветви и перехода на нее:
```
git checkout master
git checkout -b efremov_lab1
```
- Для сдачи лабораторной работы создается пул-реквест (pull-request) из вашей ветки с лабораторной работой в master-ветку общего репозитория курса. В начале заголовка пул-реквеста пишется "[READY] ", после - Фамилия латиницей, после - lab#. (Пример: [READY] Efremov lab1). Формат важен, так как для разбора ваших pull request используется поиск по ключевым словам.
- Для сдачи работы требуется закрытый pull request со слиянием (merge) вашей ветки в общий репозиторий. В таком случае работа считается проверенной.
- Если имеются какие-либо нарекания к предложенным студентом файлам, то все замечания пишутся проверяющим в комментарии пул-реквеста, а так же изменяется префикс заголовка на [WIP].
- Напоминание: коммиты в ветку, которую студент отправляет на пул-реквест отображаются в самом пул-реквесте. Делать новый пул-реквест не надо.
- Закончив исправления, студент пишет об этом отдельным комментарием, указывая, возможно, пояснения к исправлениям, а так же меняет префикс заголовка пул-реквеста снова на [READY], тем самым показывая, что его работа готова к повторному просмотру.
- Курс лабораторных считается завершенным полностью, если в основном репозитории находятся директории всех 5 лабораторных работ студента, а так же курсовой.

### Таблица посещения занятий

| ##   | ФИО                   | 24.09 | 01.10 | 08.10 | 15.10 | 22.10 | 29.10 | 05.11 | 12.11 | 19.11 | 26.11 | 03.12 | 10.12 | 17.12 | 24.12 | 31.12 |
| ---- | --------------------- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |
| 1    | Арутюнян Самвел       |   +   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 2    | Гладких Адрей         |   +   |   -   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 3    | Гордон Дмитрий        |   +   |   -   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 4    | Камзолов Никита       |   +   |   -   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 5    | Карпекина Анна        |   -   |   +   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 6    | Корсунов Антон        |   -   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 7    | Крейсманн Кирилл      |   +   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 8    | Лапина Анастасия      |   +   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 9    | Лихашва Анастаси      |   -   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 10   | Лысова Александра     |   -   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 11   | Моисейченко Кирилл    |   +   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 12   | Никифоров Павел       |   -   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 13   | Ноздрин Василий       |   -   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 14   | Орлов Даниил          |   -   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 15   | Пономаренко Софья     |   -   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 16   | Поплавский Иван       |   -   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 17   | Рыбников Роман        |   -   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 18   | Самулевич Василий     |   +   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 19   | Сергиенкова Анастасия |   -   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 20   | Хотяков Евгений       |   +   |   -   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 21   | Храпова Полина        |   -   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 22   | Чебесова Ирина        |   -   |   +   |   +   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
| 23   | Чумак Михаил          |   +   |   -   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |   .   |
