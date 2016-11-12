# arcs-dash

arcs-dash is the dashbard for arcs.

arcs-dash is a CLI interface that uses ncurses for advanced terminal usage.

## Arguments

Arguments are handled by the optarg library.
See the format in the optarg documentation.

Short | Long | Description
--- | --- | ---
`-j` | `--js-path` | Takes the next argument as the path to the joystick file
`-u` | `--user` | Takes the next argument as the remote user
`-v` | `--viewer` | Takes the next argument as the viewer IP

## Controls

Key | Description
--- | ---
`q` | Exits the dashboard
`r` | Reset networking
`0-9` | Set operation mode
`space` | Set to disabled (0)
`v` | Toggle viewer if IP is set
