# ds_wordBook

-	Program Explanation
1차 project는 영어 단어장 프로그램을 구현해야 한다. 영어 단어장에는 앞으로 외워야 할 단어장(TO_MEMORIZE), 현재 외우고 있는 단어장(MEMORIZING), 단어를 암기한 단어장(MEMORIZED)를 포함한다. 각 단어장은 각각 Queue, Binary Search Tree, Circular Linked List의 자료구조로 설계한다. 
프로그램은 명령어가 저장된 텍스트 파일로 동작을 수행하며 에러 발생 시 에러 코드를 출력하고 출력 결과에 대해서는 로그 파일에 저장된다. 각 단어장의 동작은 다음과 같다.

TO_MEMORIZE는 MOVE 명령어를 사용하여 N개의 단어를 MEMORING으로 옮길 수 있으며 새로운 단어가 들어오면 Push를 수행하여 노드에 단어를 저장하고 Pop을 통해 MEMORIZING으로 단어를 이동시킨다. TO_MEMORIZE에서 단어를 전달 하여 MEMORIZING 단어장에 저장된 단어들이 모여 BST를 이룬다. BST에는 단어들이 저장되어 있는 단어 노드와 첫 글자가 같은 노드들의 집합인 단어 BST가 있고, 알파벳의 첫 글자를 저장하는 알파벳 노드와 알파벳 노드의 집합인 알파벳 BST가 있다. 

MEMORINZG의 특징으로는 최대 100개의 단어 이하가 존재 해야하며 이를 어길 경우 MOVE 명령어에 대한 에러 코드를 출력한다. 단어 BST가 형성되는 규칙으로는 부모 노드보다 알파벳 순서가 낮은 노드는 왼쪽 서브 노드에 위치해야 하고, 알파벳 순서가 큰 노드는 오른쪽 서브 트리로 형성 되어야 한다. 단어를 외워 MEMORING의 노드가 제거 될 때에는 부모 노드의 양쪽에 자식 노드가 모두 존재할 경우, 왼쪽의 자식 노드 중 가장 큰 노드가 제거되는 노드 위치로 이동하며, 왼쪽 노드에 자식 노드가 존재 하지 않을 경우 오른쪽 자식 노드 중 가장 작은 노드가 제거되는 노드의 위치로 이동한다. 

  MEMORIZED 단어장은 MEMORIZING의 단어장에서 TEST명령어를 사용하여 단어를 외웠다고 판단 할 시에 MEMORIZED로 옮겨지고, 옮겨진 첫 단어는 Head Pointer가 가리키며 그 단어가 다시 Head Pointer를 가리키는 환형 연결 리스트구조이다. 만약 단어가 이미 존재 할 경우, Head Pointer가 가리키는 노드의 바로 뒤에 있는 노드 사이에 연결하여 단어의 중복을 피한다. 

이러한 동작을 하는 단어장은 앞서 설명하였던 것처럼 명령어에 의해 동작을 하며, 그 명령어에는 LOAD, ADD, MOVE, SAVE, TEST, SEARCH, PRINT, UPDATE가 있고 만약 명령어의 오류 및 잘못된 인자 값에 의한 에러 코드를 출력 한다. 그에 해당하는 에러 코드와 명령어의 세부 동작 및 프로그램 설계에 대한 요구사항과 이번 프로젝트에서 사용한 추상 자료형에 대한 설명은 아래에서 확인이 가능하다.


