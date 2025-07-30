#include <iostream>
#include <vector>
#include <algorithm>

struct Job {
    char id;      // 작업 ID
    int deadline; // 마감일
    int profit;   // 이익
};

// 작업을 이익(profit) 기준으로 내림차순 정렬하기 위한 비교 함수
bool compareJobs(const Job& a, const Job& b) {
    return a.profit > b.profit;
}

// 데드라인 스케줄링 메인 함수
void scheduleJobs(std::vector<Job>& jobs) {
    // 1. 모든 작업을 이익(profit) 기준으로 내림차순 정렬합니다.
    std::sort(jobs.begin(), jobs.end(), compareJobs);

    // 2. 시간 슬롯을 추적하기 위한 배열을 준비합니다.
    // 가장 먼 마감일을 찾아 배열의 크기를 결정합니다.
    int maxDeadline = 0;
    for (const auto& job : jobs) {
        if (job.deadline > maxDeadline) {
            maxDeadline = job.deadline;
        }
    }

    // slot 배열: 각 시간 슬롯이 비어있는지 여부 (true = 사용 중, false = 비어있음)
    // result 배열: 각 시간 슬롯에 어떤 작업이 배정되었는지 저장
    std::vector<bool> slot(maxDeadline, false);
    std::vector<char> result(maxDeadline);
    int totalProfit = 0;

    // 3. 정렬된 작업을 하나씩 순회하며 최적의 슬롯에 배치합니다.
    for (const auto& job : jobs) {
        // 4. 현재 작업의 마감일부터 1일까지 역순으로 비어있는 슬롯을 찾습니다.
        //    (가장 늦게 할 수 있는 시간을 찾는 과정)
        for (int j = job.deadline - 1; j >= 0; --j) {
            // 5. 비어있는 슬롯을 찾았다면
            if (!slot[j]) {
                // 해당 슬롯에 현재 작업을 배정합니다.
                result[j] = job.id; // 결과 배열에 작업 ID 저장
                slot[j] = true;     // 슬롯을 사용 중으로 표시
                totalProfit += job.profit; // 총 이익에 현재 작업의 이익을 더함
                break; // 이 작업은 배정되었으므로 다음 작업으로 넘어감
            }
        }
    }

    // 최종 결과 출력
    std::cout << "선택된 작업 순서: ";
    for (int i = 0; i < maxDeadline; ++i) {
        if (slot[i]) {
            std::cout << result[i] << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "최대 이익: " << totalProfit << std::endl;
}

int main() {
    // 예제 작업 데이터
    std::vector<Job> jobs = {
        {'a', 2, 100},
        {'b', 1, 20},
        {'c', 2, 30},
        {'d', 1, 40},
        {'e', 3, 15}
    };

    scheduleJobs(jobs);

    return 0;
}