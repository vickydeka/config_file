<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [P4 Debugger (p4dbg) user guide](#p4-debugger-p4dbg-user-guide)
  - [List of commands](#list-of-commands)
  - [General information about the debugger](#general-information-about-the-debugger)
    - [The packet id](#the-packet-id)
    - [Special field names](#special-field-names)
  - [A more detailed list of commands](#a-more-detailed-list-of-commands)
    - [`set_wp (w)`](#set_wp-w)
    - [`unset_wp`](#unset_wp)
    - [`show_wps`](#show_wps)
    - [`break (b)`](#break-b)
    - [`delete (d)`](#delete-d)
    - [`show_bps`](#show_bps)
    - [`continue (c)`](#continue-c)
    - [`next (n)`](#next-n)
    - [`print (p)`](#print-p)
    - [`backtrace (bt)`](#backtrace-bt)
    - [`break_packet_in`](#break_packet_in)
    - [`remove_packet_in`](#remove_packet_in)
    - [`stop_packet_in`](#stop_packet_in)
    - [`resume_packet_in`](#resume_packet_in)
    - [`filter_notifications`](#filter_notifications)
    - [`reset`](#reset)
    - [`skip` -- experimental](#skip----experimental)
    - [`skip_all` -- experimental](#skip_all----experimental)
    - [`CLI` -- experimental](#cli----experimental)
  - [Future extensions](#future-extensions)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# P4 Debugger (p4dbg) user guide

## List of commands

Here is a full list of commands with a short description. More details will be
found for each command later in this document. The last 3 commands (`skip`,
`skip_all` and `CLI`) are still experimental.

| Command name           | Short | Description |
| ---------------------- | ----- | ----------- |
| `set_wp`               | `w`   | Sets a watchpoint on a field |
| `unset_wp`             | `N/A` | Unsets watchpoint |
| `show_wps`             | `N/A` | Lists active watchpoints |
| `break`                | `b`   | Breaks at a specific "P4 object" |
| `delete`               | `d`   | Deletes breakpoint |
| `show_bps`             | `N/A` | Lists active breakpoints |
| `continue`             | `c`   | Starts / resumes packet processing at the switch |
| `next`                 | `n`   | Go to next update (field or ???P4 context???) |
| `print`                | `p`   | Prints the value of a field |
| `backtrace`            | `bt`  | Prints a backtrace of ???P4 contexts??? entered by the packet |
| `break_packet_in`      | `N/A` | Breaks every time a packet enters the switch |
| `remove_packet_in`     | `N/A` | Undoes the break_packet_in command |
| `stop_packet_in`       | `N/A` | Prevents the switch from accepting any more packets |
| `resume_packet_in`     | `N/A` | Undoes the stop_packet_in command |
| `filter_notifications` | `N/A` | Restricts the received notifications to a subset of packets |
| `reset`                | `N/A` | Resets all the debugger???s state |
| `skip` (exp)           | `N/A` | Skips all future notifications for the current packet |
| `skip_all` (exp)       | `N/A` | Skips all future notifications for the current packet and its descendants |
| `CLI` (exp)            | `N/A` | Connects to the switch using the Runtime CLI and issues a command |

## General information about the debugger

### The packet id

Each packet going through the switch can be identified using its "full packet
id", which is of the form `<pid>.<cid>`. Note that every time you receive an
event notification in the debugger, the packet id will be included in the
displayed message.  The `<pid>` is incremented by one every time a new packet is
received by the switch. The `<cid>` is incremented by one every time a new
packet is generated by the switch in response to the same incoming packet.  The
first packet received by the switch on any ingress port will have id `0.0`. The
second packet will have id `1.0`, and so on??? So when is the `<cid>` ever used?
Let???s assume your target switch supports multicast and that packet `3.0` is
replicated 3 times (i.e. out of 3 different ports). Each one of these 3 copies
will receive a different `<cid>`, but the `<pid>` will remain the same. In our
case, the three full packet ids will be `3.1`, `3.2` and `3.3`. The same goes
for mirroring.

The debugger keeps track of the "current packet id", which is the id of the last
packet for which an event notification was received by the debugger. For several
commands (e.g. `print`), the packet id can be omitted from the parameters which
will cause the debugger to use the stored "current packet id".

### Special field names

The debugger lets you access some special fields which are not part of the
headers or metadata. All these special names start with character `$`. We only
support one for now, `$cond`, which holds the result of the last P4 condition
evaluated by the switch.  In the future, we plan on adding other such special
fields (e.g. `$action`, for the last action selected by a table lookup).  Note
that all these special fields have a 32-bit width.

## A more detailed list of commands

### `set_wp (w)`
Usage: `set_wp <field_name>`
For example,
```
set_wp ipv4.srcAddr
w ipv4.srcAddr
```

Sets a watchpoint on the provided field. For every packet, the switch will stop
running every time the field is written to, and the debugger will be
notified. Of course this does not apply to packets for which notifications are
being filtered out (see the `filter_notifications` command) or are being skipped
(see `skip` and `skip_all`). Note that a notification is generated every time a
write is done on the field, even if the field actually keeps the same value.
The field name can take the special value `$cond`, which holds the result of the
last condition evaluated.

### `unset_wp`
Usage: `unset_wp <field_name>`
For example,
```
unset_wp ipv4.srcAddr
```

Unsets a watchpoint which was previously set with the `set_wp` command.  The
debugger will stop notifying the user when a write operation is performed on the
field.

### `show_wps`
Usage: `show_wps`

Prints a list of all the currently active watchpoints.

### `break (b)`
Usage: `break <p4 object type> <p4 object name>`
For example,
```
break parser start
break pipeline ingress
b table ipv4_lpm
```

Sets a breakpoint on a given P4 object. Every time a packet is about to "enter"
this object, the switch will pause and the debugger will be notified.  The valid
"p4 object types" are: parser, parse_state, pipeline, table, condition, action,
deparser.

### `delete (d)`
Usage: `delete <p4 object type> <p4 object name>`
For example,
```
delete parser start
d pipeline ingress
```

Removes a breakpoint which was previously set with the break command.  See
`break` command description for more details and the list of valid "p4 object
types".

### `show_bps`
Usage: `show_bps`

Prints a list of all the currently active breakpoints.

### `continue (c)`
Usage: `continue`

Starts or resumes packet processing. The switch will continue processing packet
until the next watchpoint or breakpoint event, at which point it will once again
stop all packet processing.  If you forgot to set a watchpoint or breakpoint
before issuing the `continue` command you can still pause the switch by sending
an Interrupt (`Ctrl-C`) to the debugger process; you will then be able to set a
watchpoint.

### `next (n)`
Usage: `next`

Resumes packet processing until the next event. An event is either a field
modification or a packet entering a P4 object (e.g. a table).  Unlike the
`continue` command, which will only stop the switch for watchpoints and
breakpoints set by the user, `next` will stop for all events, unless the packet
triggering this event has been explicitly excluded using the
`filter_notifications` or `skip(_all)` commands.

### `print (p)`
Usage: `print <packet id> <field name>`

Prints the value of a field for a given packet.  The packet id needs to follow
the format `<pid>.<cid>`. If the packet id is omitted, the debugger will use the
"current packet id", which is the id of the last packet for which a notification
was received.

### `backtrace (bt)`
Usage: `backtrace <packet_id>`

Returns the list of P4 objects that the packet is currently traversing, in
descending order. The packet id can be omitted and the "current packet id" will
be used.

Here are examples of possible outputs:
  - `parser 'parser' -> parse state 'parse_ethernet'`
  - `pipeline 'ingress' -> table 'ipv4_lpm' -> action 'set_nhop'`

### `break_packet_in`
Usage: `break_packet_in`

When using this command, the switch will break every time a new packet is
created, unless the corresponding packet id was excluded (see
`filter_notifications`). This new packet can either be a new incoming packet
(i.e. with a new `<pid>`) or a new "copy" of the same incoming packet (i.e. same
`<pid>` but new `<cid>`).

### `remove_packet_in`
Usage: `remove_packet_in`

Cancels `break_packet_in`. No effect if `break_packet_in` was not previously
called.

### `stop_packet_in`
Usage: `stop_packet_in`

Prevents the switch from accepting any more incoming packets. Note that this
does not apply to new "copies" of a packet already being processed by the
switch.

### `resume_packet_in`
Usage: `resume_packet_in`

Cancels `stop_packet_in`. No effect if `stop_packet_in` was not previously
called.

### `filter_notifications`
Usage: `filter_notifications <packet id>*`
For example,
```
filter_notifications 7.0
filter_notifications 8.1 8.2 10.0
filter_notifications 8
filter_notifications 8 11.0 13
filter_notifications
```

Limit the event notifications displayed by the debugger to those concerning one
of these packet ids. A packet id in the list can either be a regular full packet
id of the form `<pid>.<cid>` or simply a `<pid>`, in which case all
notifications for packets with this `<pid>` will be taken into account
(independently of the value of the `<cid>`).  When `filter_notifications` is
used without any arguments (i.e. no packet ids specified), the notifications
filter will be reset and all notifications will once again be displayed by the
debugger.

### `reset`
Usage: `reset`

Resets all the debugger's state (e.g. watchpoints, breakpoints, notification
filters...).

### `skip` -- experimental
Usage: `skip`

Skips all future notifications for the "current packet id". Cannot be undone.

### `skip_all` -- experimental
Usage: `skip_all`

Skips all future notifications for the "current packet id" and all the packets
sharing the same `<pid>`. Cannot be undone.

### `CLI` -- experimental
Usage: `CLI <bmv2 runtime CLI command>`
For example,
```
CLI table_dump ipv4_lpm
```

Opens a Thrift connection to the switch and issues a standard runtime CLI
command. Only "standard" commands are supported (no multicast PRE support).

## Future extensions

We are planning on supporting the following features in the future:
  - support for stateful objects (meters, counters, registers)
  - better P4 code integration: display current P4 code, line breakpoints
  - conditional watchpoints / breakpoints (e.g. iff packet has IPv4 address
    10.0.0.1)
