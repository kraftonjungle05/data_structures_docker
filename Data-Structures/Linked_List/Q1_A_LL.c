//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */
/*문제 번호	함수 이름	설명
Q1	insertSortedLL	오름차순 정렬 상태로 삽입
Q2	moveOddItemsToBack	홀수 노드를 리스트 뒤로 이동
Q3	splitOddEvenLL	홀수/짝수 나누어 리스트 분할
Q4	alternateMergeLinkedList	두 리스트 교차 병합
Q5	concatenateLL	두 리스트 연결
Q6	frontBackSplitLL	리스트 반으로 나누기
Q7	sortedMergeLL	두 정렬 리스트 병합*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>      // 표준 입출력 함수 사용 (printf, scanf 등)
#include <stdlib.h>     // 메모리 할당 함수 사용 (malloc, free 등)

//////////////////////////////////////////////////////////////////////////////////
// 연결 리스트에 필요한 구조체 선언 부분
// 이 부분은 "자료 구조" 뼈대를 만드는 곳

typedef struct _listnode {
    int item;               // 리스트에 저장할 실제 값
    struct _listnode *next; // 다음 노드를 가리키는 포인터
} ListNode;                 // ListNode라는 이름으로 구조체 사용 가능

typedef struct _linkedlist {
    int size;               // 리스트에 들어있는 노드(값)의 개수
    ListNode *head;         // 리스트의 첫 번째 노드를 가리키는 포인터
} LinkedList;               // LinkedList라는 이름으로 구조체 사용 가능

//////////////////////////////////////////////////////////////////////////////////
// 함수 원형 선언 (아래쪽에서 정의될 함수들을 미리 선언해놓는 구역)

int insertSortedLL(LinkedList *ll, int item); // 정렬된 상태로 삽입하는 함수 (문제 핵심!)

void printList(LinkedList *ll);               // 리스트 전체를 출력하는 함수
void removeAllItems(LinkedList *ll);          // 리스트 안의 모든 노드를 삭제하는 함수
ListNode *findNode(LinkedList *ll, int index); // 특정 인덱스에 해당하는 노드를 찾는 함수
int insertNode(LinkedList *ll, int index, int value); // 특정 위치에 노드를 삽입하는 함수
int removeNode(LinkedList *ll, int index);    // 특정 위치의 노드를 삭제하는 함수

//////////////////////////////////////////////////////////////////////////////////
// 프로그램의 시작 지점 (main 함수)
// 메뉴를 출력하고 사용자 입력을 받아 동작을 선택하게 함

int main()
{
    LinkedList ll;     // 연결 리스트 선언
    int c, i, j;       // 사용자 선택, 입력값, 삽입된 위치 저장용 변수
    c = 1;             // 메뉴 루프를 돌기 위한 초기 값

    ll.head = NULL;    // 리스트의 시작을 비움 (처음엔 아무 값도 없음)
    ll.size = 0;       // 리스트 크기도 0으로 초기화

    // 사용자에게 메뉴를 출력
    printf("1: Insert an integer to the sorted linked list:\n");
    printf("2: Print the index of the most recent input value:\n");
    printf("3: Print sorted linked list:\n");
    printf("0: Quit:");

    // 사용자가 0을 입력할 때까지 계속 반복
    while (c != 0)
    {
        printf("\nPlease input your choice(1/2/3/0): "); // 사용자 입력 요청
        scanf("%d", &c); // 숫자 입력받기

        switch (c) // 입력에 따라 동작 분기
        {
        case 1:
            printf("Input an integer that you want to add to the linked list: ");
            scanf("%d", &i); // 삽입할 숫자 입력받기
            j = insertSortedLL(&ll, i); // 정렬 삽입 함수 호출, 결과 인덱스를 j에 저장
            printf("The resulting linked list is: ");
            printList(&ll); // 리스트 출력
            break;

        case 2:
            printf("The value %d was added at index %d\n", i, j); // 마지막 삽입 값 위치 출력
            break;

        case 3:
            printf("The resulting sorted linked list is: ");
            printList(&ll); // 리스트 출력
            removeAllItems(&ll); // 모든 노드 삭제 (초기화)
            break;

        case 0:
            removeAllItems(&ll); // 종료 전 메모리 정리
            break;

        default:
            printf("Choice unknown;\n"); // 잘못된 입력
            break;
        }
    }

    return 0; // 프로그램 종료
}


//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)//정렬삽입=숫자를 오름차순으로 삽입시키기
{
	/* add your code here */
	if(ll==NULL)//포인터가 널이면=리스트가 존재하지 않으면
		return -1;//삽입 실패 -1 리턴

	if(ll->size==0){//리스트가 비어있으면 
		insertNode(ll,0,item);//맨앞에, 0번인덱스에 삽입
		return 0;//삽입 위치 0 리턴
	}

	ListNode *cur=ll->head;//선언,리스트의 헤드(첫번째노드)를 가리키는 포인터cur
	int index=0;//삽입할 위치를 추적하는 변수 인덱스(0부터 시작)

	while(cur!=NULL){//커서가 널이 되기전까지 = 리스트끝까지
		if(cur->item==item)//이미 존재하면
		return -1;//삽입 안하고 -1 반환, 중복은 X

		if(cur->item>item)//현재 값이 삽입하려는 값보다 크면
		break;//여기에 넣어야하므로 종료

		cur=cur->next;//다음 노드로 이동
		index++;//위치값 증가시켜줌줌
	}
	insertNode(ll,index,item);//찾은위치에 아이템값 삽입

	return index;//삽입 이ㅜ치 인덱스반환
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){//리스트 출력 기능

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)//리스트 초기화 기능
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){//리스트 탐색(노드찾기) 기능

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){//노드삽입 기능

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){//노드 삭제 기능

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}