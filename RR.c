void RR(){
	process present; //현재 처리중인 큐
	processing pt;
	int total = 0, complete = 0, turnaround = 0, wait = 0, i = 0;
	double avr_wait = 0.0, avr_turnaround = 0.0;

	// processing_time 벡터 초기화
	for (int i = 0; i < process_num; i++)
		processing_time[i].clear();

	// 레디 큐 생성
	queue<process> readyQ;

	// 리스트 도착시간 순서대로 정렬
	sort(list, list + process_num, arrivecomp);

	// process들을 Rlist로 복사
	queue<process> Rlist;
	for (int j = 0; j < process_num; j++) {
		Rlist.push(list[j]);
		total += list[j].burst_t;
	}
	
	// 프로세스 처리
	while (i < total) {
		
		// 현재 시간(i)에서 arrive time이 i인 process가 있으면 모두 readyQ에 넣어준다
		while (1) {
			if (Rlist.size() != 0 && Rlist.front().arrive_t == i) {
				readyQ.push(Rlist.front());
				Rlist.pop();
			}
			else
				break;
		}

		// 예외처리 - 준비완료 큐에 아무것도 없음 
		if (i != total && readyQ.size() == 0) {
			cout << "RR알고리즘 중간에 공백이 생겼습니다. - 잘못된 입력입니다.";
			system("pause");
			exit(1);
		}

		// 현재 처리할 process를 readyQ에서 하나 꺼낸다
		present = readyQ.front();
		readyQ.pop();
		int number = present.number;
		int burst = present.burst_t;
		int arrive = present.arrive_t;
		pt.start = i;

		// burst <= quantum 이면 프로세스 처리 종료
		if (burst <= quantum) {

			// 남은 burst 만큼 진행하는 동안 들어온 프로세스들 readyQ에 push
			while (1) {
				if (Rlist.size() != 0 && Rlist.front().arrive_t < i + burst) {
					readyQ.push(Rlist.front());
					Rlist.pop();
				}
				else
					break;
			}

			// 현재 프로세스 끝나면 processing time 계산
			pt.end = pt.start + burst;
			pt.burst = burst;
			if (pt.burst != 0)
				processing_time[number - 1].push_back(pt);
			pt.start = pt.end; // 새로운 시작값 저장

			// 현재 process의 complete, turnaround, wait 값 
			complete = i + burst; // 현재시간 + 남은 burst
			turnaround = complete - arrive; 
			wait = complete - arrive - burst_time[number - 1]; 
			complete_time[number - 1] = complete;
			turnaround_time[number - 1] = turnaround;
			wait_time[number - 1] = wait;

			// 평균값 계산을 위해 값 누적
			avr_wait += (double)wait;
			avr_turnaround += (double)turnaround;

			// burst만큼 다음 시간으로 이동
			i = i + burst;
		}

		// quantum보다 더 많이 남았으면 quantum만큼 프로세스 처리
		else {
			// 현재 process를 quantum 만큼 진행하는 동안 들어온 프로세스들 readyQ에 push
			while (1) {
				if (Rlist.size() != 0 && Rlist.front().arrive_t < i + quantum) {
					readyQ.push(Rlist.front());
					Rlist.pop();
				}
				else
					break;
			}

			// 현재 프로세스 교체시 processing time 계산
			pt.end = pt.start + quantum;
			pt.burst = quantum;
			processing_time[number - 1].push_back(pt);
			pt.start = pt.end; // 새로운 시작값 저장

			// 현재 프로세스 처리 후 다시 readyQ로 삽입
			present.burst_t -= quantum;
			readyQ.push(present);
			i = i + quantum;
		}
	}

	//Average Turnaround & Average Waiting
	avr_turnaround /= (double)process_num;
	avr_wait /= (double)process_num;
}
