#include <iostream>
#include <string>
#include <vector>
#include <cstring>

// 최대 노드의 개수. (총 문자열 길이의 합) 정도로 넉넉하게 설정합니다.
// 예를 들어, 길이 10인 단어 10000개 -> 10000 * 10 = 100000
const int MAX_NODES = 100005; 
const int ALPHABET_SIZE = 26;

// trie 배열: 트라이의 모든 노드를 저장하는 공간입니다.
// trie[i][j]는 i번 노드의 j번째 알파벳 자식 노드가 몇 번 노드인지를 나타냅니다.
int trie[MAX_NODES][ALPHABET_SIZE];

// is_end 배열: 해당 노드에서 끝나는 단어가 있는지를 표시합니다.
// is_end[i]가 true이면, i번 노드는 어떤 단어의 끝입니다.
bool is_end[MAX_NODES];

// node_count: 현재까지 사용된 노드의 개수이자, 다음에 새로 할당할 노드의 인덱스입니다.
int node_count;


// 트라이 자료구조를 초기화하는 함수. 새로운 테스트 케이스를 시작하기 전에 호출합니다.
void init() {
    // 모든 노드 정보를 0으로 초기화합니다.
    // -1로 초기화하는 경우도 많지만, 여기서는 0번 노드를 루트로 사용하므로
    // 자식 노드가 없다는 뜻으로 0을 사용해도 무방합니다. (단, 루트의 자식은 0이 될 수 없음)
    // 확실하게 하기 위해 -1로 초기화하는 것이 더 안전할 수 있습니다.
    for (int i = 0; i < node_count; ++i) {
        memset(trie[i], 0, sizeof(trie[i]));
        is_end[i] = false;
    }
    // 루트 노드는 0번입니다. node_count를 1로 설정하여 다음 노드는 1번부터 할당되도록 합니다.
    node_count = 1; 
}

// 트라이에 문자열을 삽입하는 함수
void insert(const std::string& s) {
    // 0번 노드, 즉 루트에서부터 시작합니다.
    int current_node = 0; 
    
    // 문자열의 각 문자를 순회합니다.
    for (char ch : s) {
        // 'a' -> 0, 'b' -> 1 ...
        int c = ch - 'a';

        // 현재 노드에서 다음 문자로 가는 경로(자식 노드)가 없다면
        if (trie[current_node][c] == 0) {
            // 새로운 노드를 할당(node_count 인덱스 사용)하고 경로를 연결합니다.
            trie[current_node][c] = node_count++;
        }
        
        // 다음 문자의 노드로 이동합니다.
        current_node = trie[current_node][c];
    }
    
    // 문자열의 마지막에 해당하는 노드에 단어가 끝났음을 표시합니다.
    is_end[current_node] = true;
}

// 트라이에서 문자열을 검색하는 함수
bool search(const std::string& s) {
    int current_node = 0; // 루트에서 시작
    
    for (char ch : s) {
        int c = ch - 'a';
        
        // 다음 문자로 가는 경로가 없다면, 이 문자열은 트라이에 없습니다.
        if (trie[current_node][c] == 0) {
            return false;
        }
        
        // 경로가 있다면 이동합니다.
        current_node = trie[current_node][c];
    }
    
    // 문자열 경로를 끝까지 따라온 후,
    // 해당 위치가 '단어의 끝'으로 표시되어 있어야만 완벽한 단어가 존재하는 것입니다.
    return is_end[current_node];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    init(); // 트라이 사용 전 초기화

    // 삽입할 단어들
    insert("apple");
    insert("apply");
    insert("banana");
    insert("ban");
    
    std::cout << std::boolalpha; // bool 값을 true/false로 출력

    std::cout << "--- 단어 검색 결과 ---" << std::endl;
    std::cout << "apple: " << search("apple") << std::endl;   // true
    std::cout << "app: " << search("app") << std::endl;       // false (단어로 삽입된 적은 없음)
    std::cout << "banana: " << search("banana") << std::endl; // true
    std::cout << "ban: " << search("ban") << std::endl;       // true
    std::cout << "band: " << search("band") << std::endl;     // false

    return 0;
}