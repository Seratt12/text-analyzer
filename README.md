# text-analyzer
[![CI](https://github.com/Seratt12/text-analyzer/actions/workflows/ci.yml/badge.svg)](https://github.com/Seratt12/text-analyzer/actions/workflows/ci.yml)


HTTP-сервис на C++ (Drogon), который принимает текст и возвращает статистику по нему.

## Возможности

- Анализ текста: количество символов, слов, предложений, уникальных слов.
- Средняя длина слова (в символах, с учётом UTF-8).
- Топ-5 самых частых слов.
- Поддержка латиницы и кириллицы.
- Регистронезависимый анализ (через Boost.Locale).
- Юнит-тесты на Google Test.

## Требования

- **CMake** 3.23+
- **C++20**-совместимый компилятор (MSVC 2022, GCC 11+, Clang 14+)
- **vcpkg** — менеджер зависимостей
- **Ninja** (опционально, рекомендуется)

## Установка зависимостей

Зависимости управляются через vcpkg-манифест (`vcpkg.json`). При первой сборке vcpkg установит их автоматически. Если хотите установить вручную:

```bash
vcpkg install drogon gtest boost-locale
```

## API

- `GET /status` - Проверка работоспособности сервиса.

Запрос:

```bash
curl http://localhost:3000/status
```

Ответ:

```json
{
  "status": "ok"
}
```

- `POST /analyze` - Принимает текст и возвращает статистику.

Запрос:

```bash
curl -X POST http://localhost:3000/analyze \
  -H "Content-Type: application/json" \
  -d '{"text": "Hello world. Hello again!"}'
```

Ответ:

```json
{
  "chars": 25,
  "words": 4,
  "sentences": 2,
  "unique_words": 3,
  "average_word_length": 5.0,
  "top_words": [
    { "word": "hello", "count": 2 },
    { "word": "again", "count": 1 },
    { "word": "world", "count": 1 }
  ]
}
```

Поля ответа:

| Поле | Тип | Описание |
|---|---|---|
| `chars` | integer | Количество символов (UTF-8, не байт) |
| `words` | integer | Количество слов |
| `sentences` | integer | Количество предложений |
| `unique_words` | integer | Количество уникальных слов (без учёта регистра) |
| `average_word_length` | number | Средняя длина слова в символах |
| `top_words` | array | Топ-5 самых частых слов с количеством вхождений |

## Технологии

- C++20
- Drogon — асинхронный HTTP-фреймворк
- Boost.Locale — регистронезависимая обработка UTF-8
- Google Test — юнит-тесты
- CMake — система сборки
- vcpkg — менеджер зависимостей
- jsoncpp — работа с JSON (транзитивно через Drogon)
