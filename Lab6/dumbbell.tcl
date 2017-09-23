set ns [new Simulator]
set nf [open out.nam w]
$ns namtrace-all $nf

proc finish { } {
        global ns nf
        $ns flush-trace
        close $nf
        exec nam out.nam &
        exit 0
}

proc create_topology {} {
global ns n num_node
set num_node 12

for {set i 0} {$i < $num_node} {incr i} {
	set n($i) [$ns node]
}

$ns set src_ [list 2 3 4 5 6]
$ns set dst_ [list 7 8 9 10 11]

# EDGES (from-node to-node length a b):
$ns duplex-link $n(0) $n(1) 1.5Mb 40ms DropTail
$ns duplex-link $n(0) $n(2) 10Mb 20ms DropTail
$ns duplex-link $n(0) $n(3) 10Mb 20ms DropTail
$ns duplex-link $n(0) $n(4) 10Mb 20ms DropTail
$ns duplex-link $n(0) $n(5) 10Mb 20ms DropTail
$ns duplex-link $n(0) $n(6) 10Mb 20ms DropTail
$ns duplex-link $n(1) $n(7) 10Mb 20ms DropTail
$ns duplex-link $n(1) $n(8) 10Mb 20ms DropTail
$ns duplex-link $n(1) $n(9) 10Mb 20ms DropTail
$ns duplex-link $n(1) $n(10) 10Mb 20ms DropTail
$ns duplex-link $n(1) $n(11) 10Mb 20ms DropTail

$ns duplex-link-op $n(0) $n(1) orient left
$ns duplex-link-op $n(0) $n(2) orient up
$ns duplex-link-op $n(0) $n(3) orient right-up
$ns duplex-link-op $n(0) $n(4) orient right
$ns duplex-link-op $n(0) $n(5) orient right-down
$ns duplex-link-op $n(0) $n(6) orient down
$ns duplex-link-op $n(1) $n(7) orient up
$ns duplex-link-op $n(1) $n(8) orient left-up
$ns duplex-link-op $n(1) $n(9) orient left 
$ns duplex-link-op $n(1) $n(10) orient left-down
$ns duplex-link-op $n(1) $n(11) orient down
}

create_topology
set tcp0 [new Agent/TCP]
$ns attach-agent $n(8) $tcp0
set sink0 [new Agent/TCPSink]
$ns attach-agent $n(5) $sink0
$ns connect $tcp0 $sink0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetsize_ 500
$cbr0 set interval_ 0.01
$cbr0 attach-agent $tcp0

$ns at 0.1 "$cbr0 start"
$ns at 2.0 "$cbr0 stop"
$ns at 5.0 "finish"
$ns run
