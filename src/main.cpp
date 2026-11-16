#include "dl_list.cpp"

// MAIN
//-------------------------------------------------------------------------------------------

int main(void)
{
    // FIXME error cases
    list_html_output = InitHTML("list.html");
    List list = {};
    ListConstructor(&list, 2);

    ListAddTail(&list, 10);                 // 10
    ListAddTail(&list, 20);                 // 10 20
    ListAddHead(&list, 5);                  // 5 10 20

    ListAddAfter(&list, 5252, ListFinderByIndex(&list, 1));

    ListAddAfter(&list, 25, list.tail);     // 5 10 20 15

    ListAddBefore(&list, 1, list.head);     // 1 5 10 20 15

    ListDel(&list, list.head);              // 5 10 20 15
    ListDel(&list, list.tail);              // 5 10 20
    ListDel(&list, 1);                      // 5 20


    while (list.head != 0)
        ListDel(&list, list.head);

    ListDestructor(&list);

    CloseHTML(list_html_output);

    return 0;

    // for (int i = 0; i <= 15; i++)
    //     ListAddAfter(&list, 100 + i, i);

    // ListAddBefore(&list, 52, 1);

    // PrintDLListGV(&list);
    // CompPng("pic1");
    // PrintListLikeArray(&list);
    // PrintDLList(&list);

    // ListDel(&list, 2);
    // ListAddAfter(&list, 52, 4);
    // ListAddAfter(&list, 67, 8);

    // PrintDLListGV(&list);
    // CompPng("pic2");
    // PrintListLikeArray(&list);
    // PrintDLList(&list);


    // // ListAddAfter(&list, 1000, 5);

    // VerifyList(&list);
    // ListDestructor(&list);
    // // printf("After delete list:\n");
    // VerifyList(&list);
    return 0;
}
