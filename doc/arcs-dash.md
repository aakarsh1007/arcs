# arcs-dash

arcs-dash is the dashbard for arcs.

arcs-dash is a CLI interface that uses ncurses for advanced terminal usage.

## Arguments

Arguments are handled by the optarg library.
See the format in the optarg documentation.

Short | Long | Description
--- | --- | ---
`-j` | `--js-path` | Takes the next argument as the path to the joystick file
`-r` | `--remote` | Takes the next argument as the remote IP/hostname
`-u` | `--user` | Takes the next argument as the remote user
`-e` | `--exec` | Takes the next argument as the remote file to run

## Controls

Key | Description
--- | ---
`q` | Exits the dashboard
`r` | Reset networking
