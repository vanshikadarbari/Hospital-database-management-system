//command to compile
//sudo gcc -o dbms 4.02_Final_Console_Application.c -I/usr/include/postgresql -lpq
//command to run
//./dbms
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>
#include <unistd.h>
#include<stdbool.h>
#include<sqlda.h>

int x;
char q[128],temp;
PGresult *res;
PGconn *conn;


void select_query() {
	printf("Enter Select Query: ");
	scanf("%c",&temp);
	scanf("%[^\n]s",q);
    	res = PQexec(conn, q);
    	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        	printf("No data retrieved\n");
        	PQclear(res);
    	}
    	else {
    		int rows = PQntuples(res);
		int cols = PQnfields(res);
    		printf("\n");
    		for(int i=0; i<rows; i++) {
    			for (int j=0;j<cols;j++) {
				printf("%s\t",PQgetvalue(res, i, j));
    			}
			printf("\n");
		}
	}
    	PQclear(res);
}

void update_choice(){
	printf("Write Update Statement: ");
	scanf("%c",&temp);
        scanf("%[^\n]s",q);
    	res = PQexec(conn, q);
    	if(PQresultStatus(res) != PGRES_COMMAND_OK) {
		printf("\nError: %s\n",PQerrorMessage(conn));
    	}
	else {
		printf("Update Statement ran Successfully!\n");
	}
    	PQclear(res);
}

void delete_choice(){
	printf("Write Delete Statement: ");
	scanf("%c",&temp);
        scanf("%[^\n]s",q);
    	res = PQexec(conn, q);
    	if(PQresultStatus(res) != PGRES_COMMAND_OK) {
		printf("\nError: %s\n",PQerrorMessage(conn));
		}
    	
	else {
		printf("Delete Statement ran Successfully!\n");
	}
    	PQclear(res);
}


void insert_choice() {
	int choice;
	char query[250],buf[20],c;
	printf("WHERE DO YOU WANT TO INSERT?\n1)Patient \n2)Employee \n3)Treatments available");
	printf("\nChoose the entity: ");
	scanf("%d",&choice);
	c=getchar();
	switch(choice){
		case 1:{
			char fname[100],lname[100],query[250], address[100], date[15];
			char minit,sex;
			long long int contactno;
			long long int relativecontactno;
			int patient_id;
			char pid[4];
			

			printf("First Name: ");
			scanf ("%[^\n]%*c", fname);

			printf("Middle Name: ");
			scanf (" %c", &minit);
				
			
			printf("Last Name: ");
			scanf (" %[^\n]%*c", lname);

			printf("Sex: ");
			scanf (" %c", &sex);

			printf("Date: Enter in MM//DD/YYYY format");
			scanf (" %[^\n]%*c", date);


			printf("Patient Mobile Number: ");
			scanf("%lld",&contactno);

			printf("Relative Mobile Number: ");
			scanf("%lld",&relativecontactno);

			printf("Address: ");
			scanf (" %[^\n]%*c", address);
			

			strcpy(query,"insert into patient_general_details values ('");		
			res = PQexec(conn, "select max(patient_id) from patient_general_details;");
			if (PQresultStatus(res) != PGRES_TUPLES_OK) {
       				printf("Failed to assign patient id!\n");
        			PQclear(res);
    			}
			else{
				strcpy(pid,PQgetvalue(res, 0, 0));
				int len = strlen(pid);
				for(int i=0; i<len; i++){
					patient_id = patient_id * 10 + ( pid[i] - '0' );
				}
				patient_id=patient_id+1;
			}
			fflush(stdout);
		
			/*CODE TO GENERATE INSERT QUERY IN BACK GROUND*/
			sprintf(buf,"%d",patient_id);
			strcat(query, buf);
			strcat(query,"','");

			//sprintf(buf,"%[^\n]%c",fname);
			strcat(query,fname);
			strcat(query,"','");

			sprintf(buf,"%c",minit);
			strcat(query,buf);
			strcat(query,"','");

			//sprintf(buf,"%[^\n]%c",lname);
			strcat(query,lname);
			strcat(query,"','");

			sprintf(buf,"%c",sex);
			strcat(query,buf);
			strcat(query,"',");
			
			
			sprintf(buf,"%lld",contactno);
			strcat(query,buf);
			strcat(query,",'");

			strcat(query,date);
			strcat(query,"',");


			sprintf(buf,"%lld",relativecontactno);
			strcat(query,buf);
			strcat(query,",'");

			//sprintf(buf,"%[^\n]%c",address);
			strcat(query,address);		
			strcat(query,"');");

			/*CODE TO RUN QUERY*/
			res = PQexec(conn, query);
		    	if(PQresultStatus(res) != PGRES_COMMAND_OK) {
				printf("\nError: %s\n",PQerrorMessage(conn));
    			}
			else {
				printf("AUTO-GENERATED INSERT STATEMENT ran Successfully!\n");
			}
    			PQclear(res);
			break;
		}

		case 2:{
			char fname[100],lname[100],query[250], address[100],bdate[15], joindate[15], leavedate[15], emptype[5];
			char minit,sex;
			long long int contactno;
			long long int relativecontactno;
			int emp_id;
			char empid[4];
			

			printf("First Name: ");
			scanf ("%[^\n]%*c", fname);

			printf("Middle Name: ");
			scanf (" %c", &minit);
				
			
			printf("Last Name: ");
			scanf (" %[^\n]%*c", lname);

			printf("Employee type: ");
			scanf (" %[^\n]%*c", emptype);

			printf("Sex: ");
			scanf (" %c", &sex);

			printf("Birth Date: Enter in MM//DD/YYYY format");
			scanf (" %[^\n]%*c", bdate);

			printf("Join Date: Enter in MM//DD/YYYY format");
			scanf (" %[^\n]%*c", joindate);

			printf("Leave Date: Enter in MM//DD/YYYY format");
			scanf (" %[^\n]%*c", leavedate);


			printf("Employee Mobile Number: ");
			scanf("%lld",&contactno);

			printf("Relative Mobile Number: ");
			scanf("%lld",&relativecontactno);

			printf("Address: ");
			scanf (" %[^\n]%*c", address);
			

			strcpy(query,"insert into employee values ('");		
			res = PQexec(conn, "select max(emp_id) from employee;");
			if (PQresultStatus(res) != PGRES_TUPLES_OK) {
       				printf("Failed to assign employee id!\n");
        			PQclear(res);
    			}
			else{
				strcpy(empid,PQgetvalue(res, 0, 0));
				int len = strlen(empid);
				for(int i=0; i<len; i++){
					emp_id = emp_id * 10 + ( empid[i] - '0' );
				}
				emp_id=emp_id+1;
			}
			fflush(stdout);
		
			/*CODE TO GENERATE INSERT QUERY IN BACK GROUND*/
			sprintf(buf,"%d",emp_id);
			strcat(query, buf);
			strcat(query,"','");

			strcat(query,emptype);
			strcat(query,"','");

			//sprintf(buf,"%[^\n]%c",fname);
			strcat(query,fname);
			strcat(query,"','");

			sprintf(buf,"%c",minit);
			strcat(query,buf);
			strcat(query,"','");

			//sprintf(buf,"%[^\n]%c",lname);
			strcat(query,lname);
			strcat(query,"','");

			strcat(query,bdate);
			strcat(query,"','");

			strcat(query,address);		
			strcat(query,"','");


			sprintf(buf,"%c",sex);
			strcat(query,buf);
			strcat(query,"',");
			
			
			sprintf(buf,"%lld",contactno);
			strcat(query,buf);
			strcat(query,",");


			sprintf(buf,"%lld",relativecontactno);
			strcat(query,buf);
			strcat(query,",'");

			strcat(query,joindate);
			strcat(query,"','");

			strcat(query,leavedate);
			strcat(query,"');");

			

			/*CODE TO RUN QUERY*/
			res = PQexec(conn, query);
		    	if(PQresultStatus(res) != PGRES_COMMAND_OK) {
				printf("\nError: %s\n",PQerrorMessage(conn));
    			}
			else {
				printf("AUTO-GENERATED INSERT STATEMENT ran Successfully!\n");
			}
    			PQclear(res);
			break;
		}
		case 3:{
			char tid[10], treatment_name[30];
			int did,fees;

			printf("Treatment id: ");
			scanf (" %[^\n]%*c", tid);

			
			printf("Department id: ");
			scanf("%d",&did);

			printf("Treatment name: ");
			scanf (" %[^\n]%*c", treatment_name);

			strcpy(query,"insert into treatments_available values  ('");

			strcat(query,tid);
			strcat(query,"',");

			sprintf(buf,"%d",did);
			strcat(query, buf);
			strcat(query,",'");

			strcat(query,treatment_name);
			strcat(query,"',");

			sprintf(buf,"%d",fees);
			strcat(query, buf);
			
			strcat(query,");");
			printf("%s\n",query);
			res = PQexec(conn, query);
		    	if(PQresultStatus(res) != PGRES_COMMAND_OK) {
				printf("\nError: %s\n",PQerrorMessage(conn));
    			}
			else {
				printf("AUTO-GENERATED INSERT STATEMENT ran Successfully!\n");
			}
    			PQclear(res);
			break;	
		}
		
		default:{
			printf("Please choose from choices given above.\n");
		}
	}	
}




int main()
{
    	conn = PQconnectdb("user=postgres password=postgres dbname=postgres");
	if (PQstatus(conn) == CONNECTION_BAD) {
        	fprintf(stderr, "Connection to database failed: %s\n",
            	PQerrorMessage(conn));
		exit(1);
    	}
	printf("CONNECTED TO DATABASE!\n");
	PQexec(conn,"set client_encoding to 'latin1'");
	PQexec(conn, "set search_path to hospital;");
	printf("SEARCH_PATH SET!\n");
	printf("\nChoose Option: \n");
	printf("1. Insert\n");
	printf("2. Update\n");
	printf("3. Delete\n");	
	printf("4. Query\n");
	printf("0. Exit\n\n");
	printf("Enter Option: ");
	fflush(stdin);
	
	scanf("%d",&x);
	while(x){
		if (x==1) insert_choice();
		else if (x==2) update_choice();
		else if (x==3) delete_choice();	
		else if(x==4)	select_query();

		printf("\n\nChoose Option: \n");
		printf("1. Insert\n");
		printf("2. Update\n");
		printf("3. Delete\n");	
		printf("4. Query\n");
		printf("0. Exit\n\n");
		printf("Enter Option: ");
		fflush(stdin);

		scanf("%d",&x);
	}
    	PQfinish(conn);
	return 0;
}




