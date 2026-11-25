# T03 - Test cases 

| ID | Input | Expected | Actual | Pass? |
|----|-------|----------|--------|-------|
| TC01a | data/sample | Reads all 8 feedback | Loaded 8 products, 8 feedback | Pass |
| TC04a | feedback.csv with a line whose score is 11 | Warning with line number, line skipped, program continues | Warning line 11: invalid score '11' -> skipped | Pass |
| TC04b | feedback.csv with a line whose score is abc | Warning with line number, line skipped, program continues | Warning line 12: invalid score 'abc' -> skipped | Pass |
| TC04c | feedback.csv with product_id P999 | Warning with line number, line skipped, program continues | Warning line 13: unknown product P999 -> skipped | Pass |
| TC04d | data/edge/dirty | Bad line skipped with warning | Warning line 2: invalid score '-1' -> skipped; Loaded 3 products, 1 feedback | Pass |
| TC05a | data/edge/empty | No crash | Loaded 0 products, 0 feedback | Pass |
| TC05b | Folder that does not exist | Clear error, no crash | Error: cannot open data/khong_ton_tai/products.csv | Pass |