#!/bin/sh
#
# This script generates a C header file with bit definitions for Amiga custom
# chips.
#
# Martin Aberg 2016, 2017
#
# \
if type tclsh > /dev/null 2>&1 ; then exec tclsh "$0" ${1+"$@"} ; fi
# \
if type tclsh8.6 > /dev/null 2>&1 ; then exec tclsh8.6 "$0" ${1+"$@"} ; fi
# \
if type tclsh8.5 > /dev/null 2>&1 ; then exec tclsh8.5 "$0" ${1+"$@"} ; fi
# \
echo "$0: tclsh required" ; \
exit 1

# Print bit- and field information for a register
# USAGE: printreg prefix ?field field?
# where each field can have any of the following formats:
# - name
# - {name bitnum}
# - {name bitnum mask}
proc printreg {reg} {
        set regname [string toupper [lindex $reg 0]]
        set nextnum 15
        foreach field [lrange $reg 1 end] {
                set fieldname [string toupper [lindex $field 0]]
                set bitnum $nextnum
                if {1 < [llength $field]} {
                        set bitnum [lindex $field 1]
                }
                set bname [string toupper "${regname}B_${fieldname}"]
                puts [format "%-31s %2d" "#define $bname" $bitnum]
                set nextnum [expr {$bitnum - 1}]
        }
        set nextnum 15
        foreach field [lrange $reg 1 end] {
                set fieldname [string toupper [lindex $field 0]]
                set bitmask 1
                if {2 < [llength $field] } {
                        set bitmask [lindex $field 2]
                }
                set bitnum $nextnum
                if {1 < [llength $field]} {
                        set bitnum [lindex $field 1]
                }
                set fname "${regname}F_${fieldname}"
                set hexmask [expr {$bitmask << $bitnum}]
                puts [format "%-31s 0x%04X" "#define $fname" $hexmask]
                set nextnum [expr {$bitnum - 1}]
        }
}

proc printregoffs {regname offset} {
        set regname [string toupper $regname]
        puts [format "%-23s 0x%03X" "#define ${regname}" $offset]
}


# example:
#
# list [
#       list [pre
#               [list field1 num mask]
#               [list field2 num mask]
#       ]
#       list [pre2
#               [list fielda num mask]
#               [list fielda num mask]
#       ]
# ]
# ->
# #define preB_field num
# #define preF_field (mask << num)
#
# num and mask have default values and are optional.
#
set regs [source custombits.tcl]

set hname CUSTOMBITS_H_

set now [clock seconds]
set nowstr [clock format $now -format "%Y-%m-%d"]
puts "#ifndef $hname"
puts "#define $hname"
puts ""
puts "/* This file was generated $nowstr */"
puts ""
puts "/* Bit definitions for Amiga custom chips */"
puts ""
foreach reg $regs {
        printreg $reg
        puts ""
}

puts "/* Register offsets from CUSTOMBASE */"
puts ""

set offss [source customoffs.tcl]
foreach offs $offss {
        printregoffs [lindex $offs 0] [lindex $offs 1]
}

puts ""
puts "#endif"
puts ""

