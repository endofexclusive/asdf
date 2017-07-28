# The script returns a list of {regname offs} pairs.

# Generate COLOR00..COLOR31
proc coloroffss {} {
        for {set i 0} {$i < 32} {incr i} {
                lappend offss "[format "color%02d" $i] [expr {0x180+$i*2}]"
        }
        return $offss
}

# Generate BPL1PT{H,L}..BPL6PT{H,L}
proc bplxptoffss {} {
        for {set i 1} {$i <= 6} {incr i} {
                lappend offss "[format "bpl%dpth" $i] [expr {0x0e0+($i-1)*4}]"
                lappend offss "[format "bpl%dptl" $i] [expr {0x0e2+($i-1)*4}]"
        }
        return $offss
}

return \
        " \
        {potgor  0x016} \
        {potgo   0x034} \
        {bltcon0 0x040} \
        {bltcon1 0x042} \
        {bltsize 0x058} \
        {diwstrt 0x08e} \
        {diwstop 0x090} \
        {ddfstrt 0x092} \
        {ddfstop 0x094} \
        [bplxptoffss] \
        {bplcon0 0x100} \
        {bplcon1 0x102} \
        {bpl1mod 0x108} \
        {bpl2mod 0x10a} \
        [coloroffss] \
        {beamcon0 0x1dc} \
        "

