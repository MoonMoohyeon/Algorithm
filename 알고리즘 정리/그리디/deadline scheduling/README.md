## **데드라인 스케줄링 (Deadline Scheduling) 알고리즘**

**데드라인 스케줄링**은 각 작업(Job)에 **마감일(Deadline)**과 **이익(Profit)**이 주어졌을 때, 총 이익을 최대화하는 최적의 작업 순서를 찾는 문제입니다.

이 알고리즘은 다음과 같은 중요한 가정을 전제로 합니다.
* 모든 작업은 완료하는 데 **1 단위의 시간**이 걸립니다.
* 한 번에 하나의 작업만 수행할 수 있습니다.

목표는 마감일을 어기지 않으면서 수행한 작업들의 **이익 합을 최대화**하는 것입니다.

---

## **알고리즘 설명**

데드라인 스케줄링은 탐욕 알고리즘(Greedy Algorithm)으로 해결할 수 있습니다. 핵심 전략은 매우 직관적입니다.

> **"이익(Profit)이 가장 큰 작업을 먼저 고려하되, 가능한 한 가장 늦은 시간에 배치한다."**

작업을 마감일에 가깝게 배치해야, 다른 작업들이 그 앞의 시간대를 사용할 수 있는 여지가 생겨 더 많은 고수익 작업을 포함할 기회가 늘어납니다.

#### **알고리즘 단계**

1.  **정렬**: 모든 작업을 **이익(Profit)이 높은 순**으로 내림차순 정렬합니다.

2.  **시간 슬롯 준비**: 1일부터 가능한 가장 먼 마감일까지의 시간 슬롯 배열을 준비합니다. 이 배열은 각 시간 단위의 사용 가능 여부를 추적합니다.

3.  **작업 배치**:
    * 정렬된 작업을 순서대로 하나씩 확인합니다.
    * 현재 작업의 **마감일(deadline)부터 1일까지 역순으로** 시간을 탐색하며 비어있는 가장 늦은 시간 슬롯을 찾습니다.
    * 만약 `t` 시간에 비어있는 슬롯을 찾으면, 해당 작업을 `t` 시간에 배정하고 다음 작업으로 넘어갑니다.
    * 만약 마감일까지 모든 시간 슬롯이 이미 차 있다면, 해당 작업은 수행할 수 없으므로 포기합니다.

4.  **결과**: 최종적으로 시간 슬롯에 배정된 모든 작업들의 이익을 합산하여 결과를 도출합니다.

---

## **정확성 증명 (Proof of Correctness)**

탐욕적인 선택(가장 이익이 큰 순서)이 항상 최적해를 보장하는지는 **교환 논증(Exchange Argument)**을 통해 증명할 수 있습니다.

#### **용어 정의**

* **탐욕해 (A)**: 위 알고리즘으로 찾은 해답 (작업의 집합).
* **최적해 (B)**: 가능한 최대 이익을 내는 이상적인 해답 (작업의 집합).
* 우리의 목표는 **`이익(A) = 이익(B)`** 임을 보이는 것입니다.

#### **증명 과정**

1.  만약 **A**와 **B**가 같다면 증명이 완료됩니다. 다르다고 가정하고 시작하겠습니다.

2.  두 해답이 다르므로, **A**에는 있지만 **B**에는 없는 작업이 있거나, 그 반대의 경우가 있을 것입니다.

3.  모든 작업들을 이익 순으로 정렬했을 때, **A**와 **B**가 달라지는 **첫 번째 작업**을 `j`라고 합시다. 탐욕 알고리즘은 이익 순으로 작업을 고려하므로, `j`는 **A**에는 없고 **B**에만 포함된 작업이어야 합니다.
    * (만약 `j`가 **A**에 있고 **B**에 없다면, **B**에 `j`를 추가했을 때 이익이 더 커지므로 **B**가 최적해라는 가정에 모순됩니다. 따라서 `j`는 **B**에만 있을 수 있습니다.)

4.  탐욕 알고리즘이 `j`를 선택하지 않은 이유는 단 하나입니다: `j`의 마감일까지의 모든 시간 슬롯이 `j`보다 이익이 높은 다른 작업들로 이미 채워져 있었기 때문입니다.

5.  이제 최적해 **B**를 살펴봅시다. **B**는 `j`를 포함하고 있으므로, `j`의 마감일까지의 시간 슬롯 중 하나는 비어있었거나, `j`보다 이익이 낮은 작업 `k`가 그 슬롯에 있었을 것입니다.

6.  **교환(Exchange)**:
    * 탐욕해 **A**는 `j`의 마감일까지의 모든 슬롯을 `j`보다 이익이 높거나 같은 작업들로 채웠습니다.
    * 최적해 **B**는 `j`의 마감일까지의 슬롯에 `j`를 포함하고 있으며, `j`를 제외한 다른 작업들은 `j`보다 이익이 높습니다.
    * **A**가 해당 시간대에 채운 작업들의 총 이익은, **B**가 채운 작업들의 총 이익보다 반드시 크거나 같을 수밖에 없습니다. 왜냐하면 **A**는 가능한 가장 높은 이익을 내는 작업들만으로 그 시간대를 채웠기 때문입니다.
    * 따라서, 우리는 최적해 **B**에서 `j`를 빼고, **A**에만 있고 **B**에는 없는 다른 작업을 그 자리에 넣어서 **B**의 총 이익을 최소한 유지하거나 더 높일 수 있습니다. 이 과정을 반복하면 결국 최적해 **B**를 탐욕해 **A**로 변환할 수 있습니다.

7.  **결론**:
    이러한 교환 논증을 통해, 탐욕 알고리즘이 선택한 해답 **A**의 총 이익은 임의의 최적해 **B**의 총 이익과 같다는 것을 알 수 있습니다. 따라서 **"이익이 큰 작업을 먼저, 최대한 늦게 배치하는"** 탐욕적인 전략은 항상 최적의 해를 보장합니다.