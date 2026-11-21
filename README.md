# smartretail-p8-group01

**Project P8 - Customer Feedback Logger & Experience Monitor**
Fundamentals of Programming (C++), MiiN-SmartRetail.

## 1. Team

| Name | GitHub |
|---|---|
| Yến Thư (team leader) | ythuvux |
| Bảo Nam | baoonammnguyenn |
| Sanh Thành | sthanh-1301 |

Lecturer: vvvanthe

## 2. Specification

**Input**
- `feedback.csv`: feedback_id, timestamp, store_id, product_id, nps_score, comment
- `products.csv`: product_id, name, category, brand, price, rating
- `inventory.csv` (Extension only): store_id, product_id, stock

**Processing**
- Skip invalid lines (score outside 0-10 or not a number, unknown product code) and print a warning with the line number to `cerr`.
- Classify each feedback: Promoter (9-10), Passive (7-8), Detractor (0-6). NPS = %Promoter - %Detractor.
- Tag each comment with topics (STOCKOUT, WAITING, STAFF, PRICE, STORE_ENV, CHECKOUT) by whole-word, case-insensitive keyword matching.
- Rank topics by number of feedback entries, and rank pain points using Detractor entries only.
- With `--add`: validate and append one new feedback entry to `feedback.csv`.

**Output**
- Experience report: group counts, percentages and IDs, NPS, topic breakdown, top pain points (and the stock cross-check for the Extension).

## 3. Build and run

```
g++ -std=c++17 -Wall -Wextra src/main.cpp -o bin/p8
bin/p8 data/sample
bin/p8 data/sample S001 --add
```

Usage: `p8 <data_folder> [store_id] [--add]` (default store_id = S001).

## 4. Assumptions and limitations

- CSV fields contain no commas and no Vietnamese diacritics.
- The first line of each CSV file is a header.
- Only C++ topics from sessions 1-7 are used (no classes, pointers, `std::sort`, map/set, lambdas).

## 5. What this project does NOT do

P8 only listens to and classifies customer feedback. It does not compute orders, replenishment or any other topic that belongs to a different project brief.

## 6. Task assignment table

| ID | Task | Function / file | Assignee | Reviewer | Flowchart | PR |
|---|---|---|---|---|---|---|
| T01 | Repo skeleton | `.gitignore`, PR template | Yến Thư | Bảo Nam | not needed | #1 |
| T02 | README and task table | `README.md` | Yến Thư | Sanh Thành | not needed | |
| T03 | Structs, read CSV, skip bad lines | `loadFeedback()`, `loadProducts()` | Bảo Nam | Yến Thư | yes | |
| T04 | Recursive binary search | `findProduct()` | Sanh Thành | Bảo Nam | yes | |
| T05 | **Core function: whole-word match** | `toLower()`, `containsWord()` | Bảo Nam | Sanh Thành | yes | |
| T06 | Topic tagging | `tagTopics()` | Sanh Thành | Yến Thư | yes | |
| T07 | Grouping and NPS | `npsGroup()`, NPS calculation | Yến Thư | Bảo Nam | yes | |
| T08 | Rank topics and pain points | `rankTopics()` | Sanh Thành | Bảo Nam | yes | |
| T09 | Validate and add feedback | `validFeedback()`, `addFeedback()` | Yến Thư | Sanh Thành | yes | |
| T10 | Print report | `printReport()` | Bảo Nam | Yến Thư | yes | |
| T11 | Test cases TC01-TC07 | `tests/` | Sanh Thành | Yến Thư | not needed | |
| T12 | Architecture | `docs/architecture.md` | Bảo Nam | Sanh Thành | not needed | |
| T13 | Slides | `docs/slides.pdf` | Yến Thư | Bảo Nam | not needed | |
| T14 | Extension: stock cross-check (optional) | `inventory.csv` | Sanh Thành | Yến Thư | yes | |
| T15 | Tag `final` | `git tag final` | Yến Thư | none | not needed | |

The core function (`containsWord`) is done by **Bảo Nam** (T05).

## 7. AI use and references

- Claude (Anthropic): used to explain the Git/GitHub workflow and to draft the repo skeleton, PR template and this README. Every team member reviewed and understands the content.
- References: course briefs (P8 project brief, GitHub guide, submission guide).