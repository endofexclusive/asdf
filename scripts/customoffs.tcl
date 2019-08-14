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
                lappend offss "[format "bpl%dpt"  $i] [expr {0x0e0+($i-1)*4}]"
                lappend offss "[format "bpl%dpth" $i] [expr {0x0e0+($i-1)*4}]"
                lappend offss "[format "bpl%dptl" $i] [expr {0x0e2+($i-1)*4}]"
        }
        return $offss
}

# Generate SPR0PT{H,L}..SPR7PT{H,L}
proc sprxptoffss {} {
        for {set i 0} {$i <= 7} {incr i} {
                lappend offss "[format "spr%dpt"  $i] [expr {0x120+$i*4}]"
                lappend offss "[format "spr%dpth" $i] [expr {0x120+$i*4}]"
                lappend offss "[format "spr%dptl" $i] [expr {0x122+$i*4}]"
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
        {cop1lc  0x080} \
        {cop1lch 0x080} \
        {cop1lcl 0x082} \
        {cop2lc  0x084} \
        {cop2lch 0x084} \
        {cop2lcl 0x086} \
        {copjmp1 0x088} \
        {copjmp2 0x08a} \
        {diwstrt 0x08e} \
        {diwstop 0x090} \
        {ddfstrt 0x092} \
        {ddfstop 0x094} \
        [bplxptoffss] \
        {bplcon0 0x100} \
        {bplcon1 0x102} \
        {bplcon2 0x104} \
        {bplcon3 0x106} \
        {bpl1mod 0x108} \
        {bpl2mod 0x10a} \
        [sprxptoffss] \
        [coloroffss] \
        {beamcon0 0x1dc} \
        "

