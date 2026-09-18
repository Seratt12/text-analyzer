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

### `GET /status`

Проверка работоспособности сервиса.

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

### `POST /analyze`

Принимает текст и возвращает статистику.

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

### `POST /analyze/batch`

Принимает массив текстов и возвращает массив результатов анализа в **том же порядке**.

**Запрос:**

```bash
curl -X POST http://localhost:3000/analyze/batch \
  -H "Content-Type: application/json" \
  -d '{
    "texts": [
      "Hello world. Hello again!",
      "Привет, мир!",
      "The quick brown fox jumps over the lazy dog."
    ]
  }'
```

**Тело запроса:**

| Поле | Тип | Обязательное | Описание |
|---|---|---|---|
| `texts` | array of string | да | Массив текстов для анализа |

**Ответ:**

```json
[
  {
    "source_text": "Hello world. Hello again!",
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
  },
  {
    "source_text": "Привет, мир!",
    "chars": 12,
    "words": 2,
    "sentences": 1,
    "unique_words": 2,
    "average_word_length": 6.0,
    "top_words": [
      { "word": "мир", "count": 1 },
      { "word": "привет", "count": 1 }
    ]
  },
  {
    "source_text": "The quick brown fox jumps over the lazy dog.",
    "chars": 44,
    "words": 9,
    "sentences": 1,
    "unique_words": 8,
    "average_word_length": 3.44,
    "top_words": [
      { "word": "the", "count": 2 },
      { "word": "brown", "count": 1 },
      { "word": "dog", "count": 1 },
      { "word": "fox", "count": 1 },
      { "word": "jumps", "count": 1 }
    ]
  }
]
```

Поля ответа:

| Поле | Тип | Описание |
|---|---|---|
| `source_text` | string | Исходная строка |
| `chars` | integer | Количество символов (UTF-8, не байт) |
| `words` | integer | Количество слов |
| `sentences` | integer | Количество предложений |
| `unique_words` | integer | Количество уникальных слов (без учёта регистра) |
| `average_word_length` | number | Средняя длина слова в символах |
| `top_words` | array | Топ-5 самых частых слов с количеством вхождений |

**Ограничения:**

- **Пустые тексты внутри массива** не пропускаются — для них возвращается результат с `words: 0`, `unique_words: 0`, `top_words: []`.
- **Максимальное количество текстов** за запрос - 300.

## Технологии

- C++20
- Drogon — асинхронный HTTP-фреймворк
- Boost.Locale — регистронезависимая обработка UTF-8
- Google Test — юнит-тесты
- CMake — система сборки
- vcpkg — менеджер зависимостей
- jsoncpp — работа с JSON (транзитивно через Drogon)
