The list is a circular double chain list.
When initialized, the list has a blank head node and its listsize is 1 because of the headnode. 
When inserting or erasing, you cannot do anything on the headnode located in index 1 because it is headnode and is protected by "the teacher".

Besides, this class is not perfect, the better idea is to use void* as the information in node so that we can store anything in the list by void* and we can trace back to its original address.