use gestiune_garaje

create table tipuri (
    id int identity,
	CONSTRAINT pk_tipuri PRIMARY KEY (id),
    tip varchar(50) not null,
    descriere varchar(50) not null,
);

create table garaje (
    id int identity,
	constraint pk_garaje primary key(id),
    nume varchar(50) not null,
    strada varchar(50) not null,
    numar int not null,
    localitate varchar(50) not null,
    id_tipuri int not null,
    constraint fk_tip_garaj foreign key (id_tipuri) references tipuri(id),
);

create table clienti (
	id int identity,
	constraint pk_clienti primary key (id),
	nume varchar(50) not null,
	prenume varchar(50) not null,
	gen varchar(50) not null,
	vechime int not null
)

create table unelte (
	id int identity,
	constraint pk_unelte primary key (id),
	nume varchar(50) not null,
	pret money not null,
	cantitate int not null,
	id_client int not null,
	constraint fk_clienti foreign key (id_client) references clienti(id)
)

create table activitati (
	id_clienti int,
	id_garaje int,
	constraint pk_activitati primary key (id_clienti, id_garaje),
	constraint fk_clienti_activitati foreign key (id_clienti) references clienti(id),
	constraint fk_garaje_activitati foreign key (id_garaje) references garaje(id),
	beneficiu varchar(50) not null,
	data_activitatii datetime not null
)

go
create or alter procedure upsert_activitati
@id_client int,
@id_garaj int,
@beneficiu varchar(50),
@data_activitatii datetime
as
begin
	if exists(select * from activitati where activitati.id_clienti=@id_client and activitati.id_garaje=@id_garaj)
	begin
		update activitati set data_activitatii=@data_activitatii, beneficiu=@beneficiu where activitati.id_clienti=@id_client and activitati.id_garaje=@id_garaj
	end
	else
	begin
		insert into activitati (id_clienti, id_garaje, beneficiu, data_activitatii)
		values (@id_client, @id_garaj, @beneficiu, @data_activitatii)
	end
end

insert into tipuri(tip, descriere) values ('mare', 'garaj mare'),('mic', 'garaj mic')
insert into garaje(nume, strada, numar, localitate, id_tipuri) values ('garaj 1', 'strda', 5, 'vl', 1),('garaj 2', 'strda', 3, 'cj', 2)
insert into clienti(nume, prenume, gen, vechime) values ('andrei', 'diaconescu', 'barbat alfa', 1),('teo', 'domnica', 'barbat beta', 0)
insert into unelte(nume, pret, cantitate, id_client) values('ciocan', 100, 10, 1), ('roaba', 500, 2, 2), ('surubelnita', 50, 100, 1)


exec upsert_activitati 1,1,'masini',2020

exec upsert_activitati 2,1,'masini',2020
exec upsert_activitati 2,2,'masini',2020

exec upsert_activitati 1,1,'macarale',2020

go
create view pula as
select clienti.prenume, clienti.nume, count(clienti.nume) as numar_de_garaje
from activitati join clienti on clienti.id=activitati.id_clienti
group by clienti.nume, clienti.prenume
having count(clienti.nume) >= 1

