create schema hospital
set search_path to hospital


CREATE TABLE patient_general_details (
patient_id DECIMAL(9,0),
fname VARCHAR(20) NOT NULL,
minit CHAR(1),
lname VARCHAR(20),
sex CHAR(1),
contact_no varchar(15) NOT NULL,
bdate DATE,
relative_contact_no varchar(15),
address VARCHAR(30),
PRIMARY KEY (patient_id)
);


CREATE TABLE patient_medical_conditions (


patient_id DECIMAL(9,0),
medical_history VARCHAR(50),
primary key(patient_id,medical_history),
foreign key(patient_id) references patient_general_details(patient_id)
ON DELETE SET DEFAULT ON UPDATE CASCADE
);


CREATE TABLE employee (
emp_id DECIMAL(9,0),
emp_type varchar(3) NOT NULL,
fname VARCHAR(20) NOT NULL,
minit CHAR(1),
lname VARCHAR(20),
bdate DATE,
address VARCHAR(30) NOT NULL,
sex CHAR(1),
contact_no varchar(15) NOT NULL,
relative_contact_no varchar(15),
date_of_join DATE NOT NULL,
date_of_resign DATE ,
PRIMARY KEY (emp_id)
);




CREATE TABLE room_type
(
room_type varchar(30),
room_abbrev varchar(4),
charge_per_bed int NOT NULL,
PRIMARY KEY (room_type)
);
create type room_no_type as enum('GW001',
'SSP002',
'SP003',
'DX004',
'SSP005',
'SU101',
'SSP102',
'SSP103',
'SP104',
'DX105',
'ICU201',
'OT202',
'SU203',
'SSP204',
'OT301',
'OT302',
'SP303',
'GW304',
'DX305',
'GW401',
'SU402',
'OT403',
'DX404',
'SSP405' );


CREATE TABLE room_details(
room_no room_no_type,
room_type varchar(5) NOT NULL,
capacity int NOT NULL,
no_of_beds_occupied int,
PRIMARY KEY (room_no),
Foreign key (room_type) references room_type(room_abbrev)
ON DELETE SET DEFAULT ON UPDATE CASCADE
);




CREATE TABLE department (
dep_no SMALLINT,
dep_name VARCHAR(25) NOT NULL,


dep_head_id DECIMAL(9,0),
PRIMARY KEY (dep_no)
);


Create table doctors
(
emp_id DECIMAL(9,0),
qualification varchar(30),
dep_no smallint NOT NULL,
primary key(emp_id),
foreign key (emp_id) references employee(emp_id),    
foreign key (dep_no) references department(dep_no)
ON DELETE SET DEFAULT ON UPDATE CASCADE
);


ALTER table department add FOREIGN KEY (dep_head_id) REFERENCES
doctors(emp_id);


Create table medical_equipment_details
(
equipment_id int,
dep_no smallint NOT NULL,
name varchar(50) NOT NULL,
cost int NOT NULL,
type char(1) NOT NULL,
stock int,
reorderlevel int,
primary key(equipment_id,dep_no)
foreign key (dep_no) references department(dep_no)


);






create table opd
(
emp_id DECIMAL(9,0),
consulting_fees int,
primary key(emp_id),
foreign key (emp_id) references doctors(emp_id)
on delete cascade on update cascade
);
create table opd_availability
(
emp_id DECIMAL(9,0),
days char(3) ,
entry_time time ,
exit_time time,
primary key(emp_id,days),
foreign key (emp_id) references opd(emp_id)
on delete cascade on update cascade
);


create table opd_attendance
(
emp_id DECIMAL(9,0),
dates date ,                                              
in_time time,
out_time time,
primary key(emp_id,dates),
foreign key (emp_id) references opd(emp_id)
on delete cascade on update cascade
);




create table specialised_doctor
(
emp_id DECIMAL(9,0),
charge_per_visit int,
primary key(emp_id),
foreign key (emp_id) references doctors(emp_id)
on delete cascade on update cascade
);


create table specialised_doctor_visit
(
emp_id DECIMAL(9,0),
dates date,                                              
in_time time,
out_time time,
primary key(emp_id,dates),
foreign key (emp_id) references specialised_doctor(emp_id)
on delete cascade on update cascade
);




create table general_staff
(
emp_id DECIMAL(9,0),
charge_per_hour int not null,


primary key(emp_id),
foreign key (emp_id) references employee(emp_id)
on delete cascade on update cascade
);






create table attendance_log_general
(
emp_id DECIMAL(9,0),
dates date,
in_time timestamp,                            
out_time timestamp,
shift_type char(1),
primary key(dates,emp_id),
foreign key (emp_id) references employee(emp_id)
on delete cascade on update cascade
);


create table treatments_available
(
tid varchar(10),
did smallint not null,
treatment_name varchar(50) not null,
fees int,   
primary key(tid),
foreign key (did) references department(dep_no)
on delete cascade on update cascade                   
);


create table policy_details
(
policy_No varchar(15),
policy_type varchar(30),
company_id smallint not null,
company_name varchar(30),
cashless_availability char(1),                      
claim_amt int,
primary key(policy_no)
);


create table patient_insurance_details
(
policy_no varchar(15),
patient_id decimal(9,0),
primary key(patient_id,policy_no),
foreign key(policy_no) references policy_details,
foreign key (patient_id) references patient_general_details(patient_id)
on delete cascade on update cascade
);








create table consultation_bill
(
case_C_no decimal(9,0),
pid DECIMAL(9,0) not null,
dr_id DECIMAL(9,0) not null,
consultation_charges int,
extra_charges int,
diagnosis varchar(30),
bill_date timestamp not null,
total_charges int not null,
primary key (case_c_no),
foreign key(pid) references patient_general_details(patient_id),
foreign key (dr_id) references opd(emp_id)
on update cascade on delete cascade
);




create table admitted
(
case_A_number decimal(9,0),
patient_id decimal (9,0) not null,
admit_date date not null,
discharge_date date,
room_no room_no_type not null,
primary key(case_a_number),
foreign key (patient_id) references patient_general_details(patient_id),
foreign key (room_no) references room_details(room_no)
on update cascade on delete cascade
);






create table intermediate_bill
(
case_A_no DECIMAL(9,0),
bill_id DECIMAL(9,0),
patient_id DECIMAL(9,0) not null,
bill_date date not null,
treatment_id varchar(10),
room_no room_no_type,
room_charges int,
treatment_charges int,
diagnosis varchar(35),
specialised_dr_id DECIMAL(9,0),
opd_dr_id DECIMAL(9,0),
specialised_dr_charge int,
opd_dr_charge int,
total_charge int,
primary key(case_A_no,bill_id),
foreign key(case_A_no) references admitted(case_A_number),
foreign key(patient_id) references patient_general_details(patient_id),
foreign key(treatment_id) references treatments_available(tid),
foreign key(room_no) references room_details(room_no),
foreign key(specialised_dr_id) references specialised_doctor(emp_id),
foreign key(opd_dr_id) references opd(emp_id)
on delete cascade on update cascade
);


create table final_bill
(
case_A_no decimal(9,0),
patient_id DECIMAL(9,0) not null,
policy_no varchar(30),
insurance_status char(1),
claim_per_passed  decimal(9,2),
claim_amt_passed decimal(9,2),
total_charges int,
amt_payable decimal(9,2),
primary key(case_A_no),
foreign key(patient_id) references patient_general_details(patient_id),
foreign key(policy_no) references policy_details(policy_no),
foreign key(case_A_no) references admitted(case_A_number)
on delete cascade on update cascade
);


create table discharge_summary
(
case_A_no decimal(9,0),
pid decimal(9,0),
Diagnosis_details varchar(100),
patient_status char(20),           
primary key(case_A_no),
foreign key (case_A_no) references Admitted (case_A_number),
foreign key (pid) references patient_general_details(patient_id)
on delete cascade on update cascade             
)