create database ebay_db_manual;

use ebay_db_manual;

create table address (
	id bigint identity,
	constraint pk_address primary key(id),
	country varchar(50) not null,
	city varchar(50) not null,
	street varchar(50) not null,
	postal_code varchar(50) not null,
)

create table buyer (
	id bigint,
	constraint pk_buyer primary key(id),
	name varchar(50) not null,
	email varchar(50) not null,
	address_id bigint foreign key references address(id) ON DELETE CASCADE ON UPDATE CASCADE,
)

create table seller (
	id bigint identity,
	constraint pk_seller primary key(id),
	name varchar(50) not null,
	email varchar(50) not null,
	address_id bigint foreign key references address(id) ON DELETE CASCADE ON UPDATE CASCADE,
)

create table category (
	id bigint identity,
	constraint pk_category primary key(id),
	name varchar(50) not null,
)

create table product (
	id bigint identity,
	constraint pk_product primary key(id),
	name varchar(50) not null,
	created_date datetime not null,
	price money not null,
	seller_id bigint foreign key references seller(id) ON DELETE CASCADE ON UPDATE CASCADE,
	category_id bigint foreign key references category(id) ON DELETE CASCADE ON UPDATE CASCADE,
)

create table transporter (
	id bigint identity,
	constraint pk_transporter primary key(id),
	name varchar(50) not null,
	price_per_km money not null,
)

create table sale (
	buyer_id bigint foreign key references buyer(id) ON DELETE CASCADE ON UPDATE CASCADE,
	product_id bigint foreign key references product(id),
	transaction_date date not null,
	constraint pk_sale primary key(buyer_id, product_id, transaction_date),
	transporter_id bigint foreign key references transporter(id) ON DELETE CASCADE ON UPDATE CASCADE,
)

create table employee (
	id bigint identity,
	constraint pk_employee primary key(id),
	name varchar(50) not null,
	salary money not null,
	hours_per_day datetime not null,
	address_id bigint foreign key references address(id) ON DELETE CASCADE ON UPDATE CASCADE,
)

create table department (
	id bigint identity,
	constraint pk_department primary key(id),
	name varchar(50) not null,
)

create table employee_department (
	employee_id bigint foreign key references employee(id),
	department_id bigint foreign key references department(id),
	constraint pk_employee_department primary key(employee_id, department_id),
	starting_date datetime not null,
)


