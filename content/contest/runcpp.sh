#!/bin/bash
# chmod +x runcpp.sh
runcpp() {
    if [ "$#" -ne 1 ]; then
        echo "Usage: runcpp <cpp_file>"
        return 1
    fi
    g++ -std=c++17 -o program_name "$1" && ./program_name < input.in > output.in
    # Check if the output matches the expected output
    if diff -q output.in expected_output.in >/dev/null; then
        echo "Output matches expected output."
    else
        echo "Output does not match expected output."
        echo "Differences:"
        diff output.in expected_output.in
    fi
}
# Call the function if script is run
if [ "$#" -eq 1 ]; then
    runcpp "$1"
else
    echo "Please provide a C++ file."
fi
