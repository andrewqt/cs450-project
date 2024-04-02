#!/bin/bash

commands=(
    "bfs"
    "dfs"
    "hld"
    "naive"
    "stack_dfs"
)

tests=(
    "line_tree"
    "random_tree"
)

output="out.txt"
echo "test,nodes,queries,algo,init time,search time,table build time,preprocess time,query time,total time" > $output

for test in "${tests[@]}"; do
    echo "$test"
    queries=1000000
    nodes=100
    while ((nodes <= 1000000)); do 
        # generate data
        data="data/$test-$nodes-$queries"
        eval "./$test $nodes $queries 69 $data"

        echo "$nodes"
        for cmd in "${commands[@]}"; do
            echo "Executing command: $cmd"
            for ((i = 0; i<10; i++)) 
            do
                echo -n "$test,$nodes,$queries,$cmd," >> $output
                # add time results
                eval "./$cmd < $data | tail -n +2 | cut -d \":\" -f2 | cut -d ' ' -f2 | awk '{printf \"%s%s\",sep,\$0; sep=\",\"} END{print \"\"}' >> $output"
            done
        done
        (( nodes *= 10))
    done
done