# Charge Validation Tool

This is a tool to validate charging parameters.

Given a set of values, it checks if they have 'sudden jumps'.
Such jumps indicate a failed / noisy sensor.

## Tasks

1. The 'No Duplications' check is failing. Resolve the duplication.
1. Give a good name to the function `_give_me_a_good_name`.
It is a boolean function, used in `if` statements.
Ensure that the `if` statement reads like a sentence after you rename the function.
1. The `values` parameter, given to the `validate...` function can be null.
Currently, the code does not handle that.
Ensure the code ignores a call with a null-pointer and add a test for that.
