#include <iostream>
#include <vector>
#include <algorithm>

struct Job{
	uint16_t deadline;
	uint16_t profit;
};

template <typename T>
struct Slots{
	Slots(std::vector<T> &ref): slots(ref) {};
	std::vector<T>& slots;
	T& firstSlot( T& deadline ){
		if( slots[deadline] == deadline ) return slots[deadline];
		else return slots[deadline] = firstSlot(slots[deadline]);
	}
};

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	const uint16_t N_MAX = 100;
	uint16_t T;
	uint16_t N;

	std::vector<Job> jobs;
	jobs.reserve(N_MAX);

	std::vector<uint16_t> slots;
	slots.reserve(N_MAX+1);
	Slots<uint16_t> slotty(slots);

	uint16_t skip, mySlot;
	uint16_t maxProfit, numJobs;
	uint16_t lastDeadline;

	std::cin >> T;
	while (T--){

		std::cin >> N;
		jobs.resize(N);

		lastDeadline = 0;
		for( auto &job: jobs ){
			std::cin >> skip >> job.deadline >> job.profit;
			if( job.deadline > lastDeadline ) lastDeadline = job.deadline;
		}
		slots.resize(lastDeadline+1);
		for( auto time = slots.begin(); time != slots.end(); time++)
			*time = time-slots.begin();
		
		std::sort( jobs.begin(), jobs.end(), [](Job& a, Job& b){ return a.profit > b.profit; } );
		maxProfit = 0;
		numJobs = 0;
		for( auto &job: jobs ) 
			if( mySlot = slotty.firstSlot( job.deadline ) ){ 
				/*std::cout << job.profit <<",d:"<<job.deadline<<" at "<< mySlot <<'\t'; */
				slots[mySlot] = slots[mySlot-1];
				maxProfit += job.profit;
				numJobs++;
				if( !--lastDeadline ) break;
			}

		std::cout << numJobs << ' ' << maxProfit << '\n';
	}
	std::cout << std::flush;

	return 0;
}
