BEGIN {
	for(i = 1; i < 7; i++)  {
		send2[i] = 0;
		recv2[i] = 0;
	}
} 

#Count cbr packets received on node 5 from flow 2(from node 1) in each interval
$1 == "r" && $8 == 2 && $5 == "cbr" && $4 == 5 && $2 >= 1.0 && $2 <= 45.0 {
        if($2 >= 1.0 && $2 < 2.0) {
                recv2[1]++;
        } else if($2 >= 2.0 && $2 < 10.0) {
                recv2[2]++;
        } else if($2 >= 10.0 && $2 < 15.0) {
                recv2[3]++;
        } else if($2 >= 15.0 && $2 < 20.0) {
                recv2[4]++;
        } else if($2 >= 20.0 && $2 < 30.0) {
                recv2[5]++;
        } else if($2 >= 30.0 && $2 <= 45.0) {
                recv2[6]++;
        }
}

#Count cbr packets sent from node 1 on flow 2(to node 5) in each interval
$1 == "+" && $8 == 2 && $5 == "cbr" && $3 == 1 && $2 >= 1.0 && $2 <= 45.0 {
        if($2 >= 1.0 && $2 < 2.0) {
                send2[1]++;
        } else if($2 >= 2.0 && $2 < 10.0) {
                send2[2]++;
        } else if($2 >= 10.0 && $2 < 15.0) {
                send2[3]++;
        } else if($2 >= 15.0 && $2 < 20.0) {
                send2[4]++;
        } else if($2 >= 20.0 && $2 < 30.0) {
                send2[5]++;
        } else if($2 >= 30.0 && $2 <= 45.0) {
                send2[6]++;
        }
}

END {
	for(i = 1; i < 7; i++) {
		if(send2[i] == 0) {
			printf "%d\t%f\n",i,0;
		} else {
                	printf "%d\t%f\n",i,(recv2[i]/send2[i])*100;
		}
        }
}
