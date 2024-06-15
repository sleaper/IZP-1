# Virtual Keyboard Address Filter
This project simulates the functionality of a virtual keyboard in a car navigation system that dynamically enables or disables keys based on the input string to help users find addresses quickly.

## Functionality
- Input: The program reads known addresses from standard input (stdin).
- Output: The program prints:
  - Found: ADDRESS if a single matching address is found.
  - Enable: CHARS if multiple addresses match the input, listing possible next characters.
  - Not found if no addresses match the input.

 ## Example

 ```bash
$ echo "Praha\nBrno\nBruntal\nBratislava" | ./keyfilter
Enable: BP
$ echo "Praha\nBrno\nBruntal\nBratislava" | ./keyfilter b
Enable: R
$ echo "Praha\nBrno\nBruntal\nBratislava" | ./keyfilter br
Enable: ANU
$ echo "Praha\nBrno\nBruntal\nBratislava" | ./keyput brn
Found: BRNO
$ echo "Praha\nBrno\nBruntal\nBratislava" | ./keyput be
Not found
```
