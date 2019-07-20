1NF idicates, that all values of the columns are atomic, meaning they contain no repeating values.

2NF: table in 1NF and partial dependencies are removed. Partial dependency means the fields contained in a row (record) depend on only one portion of the primary key.

3NF: table in 2NF and all transitive dependencies are removed. A transitive functional dependency is when changing a non-key column, might cause any of the other non-key columns to change.

Steps:
1NF: Eliminate all repeating values and identify a primary key or primary composite key.
2NF: Make certain the table is in 1NF and eliminate any partial dependencies.
3NF: Make certain the table is in 2NF and remove any transitive dependencies.




