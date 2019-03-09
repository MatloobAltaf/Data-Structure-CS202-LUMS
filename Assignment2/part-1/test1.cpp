#include "tree.cpp"


int main()
{
	bool status = 1;
	// make a tree
	cout<<"Testing VCS Tree!!!\n";
	Tree t("A();");
	t.branch(1);
	t.branch(1);
	t.branch(1);
	t.commit(11,"B();");
	t.commit(12,"C();");
	t.commit(13,"D();");

	t.branch(11);
	t.branch(11);
	t.branch(11);
	t.commit(111,"E();");
	t.commit(112,"F();");
	t.commit(113,"G();");

	t.branch(12);
	t.branch(12);
	t.branch(12);
	t.commit(121,"H();");
	t.commit(122,"I();");
	t.commit(123,"J();");

	
	// test t.get_node and branch


	bool t1= 1;
	cout << "Testing branch and Get Node";

	if(t.get_node(1)->latest_data != "A();"){
		t1 =0;
	} else {
		cout << ".";
	}
	if(t.get_node(11)->latest_data != "A();B();"){
		t1 =0;
	} else {
		cout << ".";
	}
	if(t.get_node(113)->latest_data != "A();B();G();"){
		t1 =0;
	} else {
		cout << ".";
	}
	if(t.get_node(121)->latest_data != "A();C();H();"){
		t1 =0;
	} else {
		cout << ".";
	}

	if(t.get_node(21) != 0){
		t1 =0;
	} else {
		cout << ".";
	}

	if(t.get_node(1234) != 0){
		t1 =0;
	} else {
		cout << ".";
	}

	if(t1){
		cout << "Passed!" << endl;
	} else {
		cout << " Failed!!" << endl;
	}


	// test_merge 
	bool t2 = 1;
	cout << "Testing Merge";


	t.merge(111,121);
	t.merge(123,13);
	t.merge(212, 123);

	if (t.get_node(121)->latest_data != "A();C();H();A();B();E();") {
	 t2 = 0;
	} else {
		cout << ".";
	}

	if (t.get_node(13)->latest_data != "A();D();A();C();J();") {
	 t2 = 0;
	} else {
		cout << ".";
	}

	if (t.get_node(123)->latest_data != "A();C();J();") {
	 t2 = 0;
	} else {
		cout << ".";
	}

	if(t2){
		cout << "Passed!" << endl;
	} else {
		cout << " Failed!!" << endl;
	}

	cout << "Testing Commit and get_file";

	// test_commit and get file
    bool t3 = 1;
	t.commit(13,".");
	t.commit(13,".");

	
	if(t.get_file(13,0) != "A();"){
		t3 =0;
	} else {
		cout << ".";
	}

	if(t.get_file(13,1) != "A();D();A();C();J();"){
		t3 =0;
	} else {
		cout << ".";
	}

	if(t.get_file(13,2) != "A();D();A();C();J();."){
		t3 =0;
	} else {
		cout << ".";
	}

	if(t.get_file(13,3) != "A();D();A();C();J();.."){
		t3 =0;
	} else {
		cout << ".";
	}

	if(t.get_file(21,0) != ""){
		t3 =0;
	} else {
		cout << ".";
	}

	if(t.get_file(194,0) != ""){
		t3 =0;
	} else {
		cout << ".";
	}

	if(t3){
		cout << "Passed!" << endl;
	} else {
		cout << " Failed!!" << endl;
	}

	// test_merge_history
    bool t4 =1;
	vector<merge_state> my_history = t.merge_history();

	bool a = my_history[0].src_id == 111;
	bool b = my_history[0].dst_id == 121;
	bool c = my_history[1].src_id == 123;
	bool d = my_history[1].dst_id == 13;

	if(a && b && c && d && my_history.size() ==2){
		cout << "Test merge_history ... Passed!!!" << endl;
	} else {
		cout << "Test merge history Failed!!" << endl;
	}


	// tree traversal
    cout << "---- level order tree traversal -------- " << endl;

    t.level_traversal();
}
