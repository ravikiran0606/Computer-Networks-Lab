BEGIN {
	for(i = 1; i < 7; i++)  {
		send1[i] = 0;
		recv1[i] = 0;
	}
} 

#Count cbr packets received on node 5 from flow 1(from node 0) in each interval
$1 == "r" && $8 == 1 && $5 == "cbr" && $4 == 5 && $2 >= 1.0 && $2 <= 45.0 { 
	if($2 >= 1.0 && $2 < 2.0) {
		recv1[1]++;
	} else if($2 >= 2.0 && $2 < 10.0) {
		recv1[2]++;
	} else if($2 >= 10.0 && $2 < 15.0) {
		recv1[3]++;
	} else if($2 >= 15.0 && $2 < 20.0) {
		recv1[4]++;
	} else if($2 >= 20.0 && $2 < 30.0) {
		recv1[5]++;
	} else if($2 >= 30.0 && $2 <= 45.0) {
		recv1[6]++;
	}
}

#Count cbr packets sent from node 0 on flow 1(to node 5) in each interval
$1 == "+" && $8 == 1 && $5 == "cbr" && $3 == 0 && $2 >= 1.0 && $2 <= 45.0 {
        if($2 >= 1.0 && $2 < 2.0) {
                send1[1]++;
        } else if($2 >= 2.0 && $2 < 10.0) {
                send1[2]++;
        } else if($2 >= 10.0 && $2 < 15.0) {
                send1[3]++;
        } else if($2 >= 15.0 && $2 < 20.0) {
                send1[4]++;
        } else if($2 >= 20.0 && $2 < 30.0) {
                send1[5]++;
        } else if($2 >= 30.0 && $2 <= 45.0) {
                send1[6]++;
        }
}

END {
	for(i = 1; i < 7; i++) {
                if(send1[i] == 0) {
                        printf "%d\t%f\n",i,0;
                } else {
                        printf "%d\t%f\n",i,(recv1[i]/send1[i])*100;
                }
        }

}
