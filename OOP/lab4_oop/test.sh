#!/bin/bash

echo "=== pdadd ==="
./pdadd 20221101 <<< $'Today is a lovely day.\n.'
./pdadd 20221102 <<< $'Had a great lunch.\n.'
./pdadd 20221103 <<< $'Finished my assignment.\n.'

echo "=== pdlist (all) ==="
./pdlist

echo "=== pdlist (range 20221101 - 20221102) ==="
./pdlist 20221101 20221102

echo "=== pdshow 20221101 ==="
./pdshow 20221101

echo "=== pdremove 20221101 ==="
./pdremove 20221101

echo "=== pdlist after remove ==="
./pdlist