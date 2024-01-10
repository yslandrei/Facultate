create database test

use test

create table clienti (
	id int primary key identity,
	nume varchar(50) not null,
	prenume varchar(50) not null,
	gen varchar(50) not null,
	data_nastere datetime not null
);

create table apartamente (
	id int primary key identity,
	numar int not null,
	etaj int not null,
	scara varchar(50) not null,
	bloc varchar(50) not null,
	strada varchar(50) not null,
	localitate varchar(50) not null,
);

create table chirii (
	id int primary key identity,
	numar int not null,
	luna varchar(50) not null,
	valoare money not null,
	data_plata datetime not null,
	client_id int foreign key references clienti(id),
	apartament_id int foreign key references apartamente(id),
);

create table bunuri (
	id int primary key identity,
	denumire varchar(50) not null,
	descriere varchar(50) not null,
	pret money not null,
);

create table achizitii (
	bun_id int,
	apartament_id int,
	constraint pk_achizitii primary key (bun_id, apartament_id),
	constraint fk_bunuri_achizitii foreign key (bun_id) references bunuri(id),
	constraint fk_apartamente_achizitii foreign key (apartament_id) references apartamente(id),
	data_achizitie datetime not null,
	cantitate int not null,
	pret money not null
);


INSERT INTO clienti (nume, prenume, gen, data_nastere) VALUES
('Popescu', 'Ion', 'Masculin', '1990-05-15'),
('Ionescu', 'Maria', 'Feminin', '1985-08-22'),
('Radu', 'Alexandru', 'Masculin', '1982-12-10');

INSERT INTO apartamente (numar, etaj, scara, bloc, strada, localitate) VALUES
(101, 2, 'A', 'A1', 'Strada Principala', 'Bucuresti'),
(202, 5, 'B', 'B2', 'Strada Larga', 'Cluj-Napoca'),
(303, 3, 'C', 'C3', 'Strada Inalta', 'Iasi');

INSERT INTO chirii (numar, luna, valoare, data_plata, client_id, apartament_id) VALUES
(102, 'Ianuarie', 1000, '2024-01-05', 1, 2),
(101, 'Ianuarie', 800, '2024-01-05', 1, 1),
(202, 'Februarie', 1000, '2024-02-10', 2, 2),
(303, 'Martie', 1200, '2024-03-15', 3, 3);

INSERT INTO bunuri (denumire, descriere, pret) VALUES
('Set Mobilier', 'Mobila pentru sufragerie', 2000),
('Electrocasnice Bucatarie', 'Gadget-uri de bucatarie moderne', 1500),
('Electronice', 'Televizor smart si gadget-uri', 2500);

INSERT INTO achizitii (bun_id, apartament_id, data_achizitie, cantitate, pret) VALUES
(1, 1, '2024-01-01', 1, 2000),
(2, 2, '2024-02-02', 2, 3000),
(3, 3, '2024-03-03', 1, 1500);


go
create or alter procedure upsert_achizitii
@apartament_id int,
@bun_id int,
@data_achizitie varchar(50),
@cantitate int,
@pret money
as
begin
	if exists(select * from achizitii where achizitii.apartament_id=@apartament_id and achizitii.bun_id=@bun_id)
	begin
		update achizitii set data_achizitie=@data_achizitie, cantitate=@cantitate, pret=@pret 
		where achizitii.apartament_id=@apartament_id and achizitii.bun_id=@bun_id
	end
	else
	begin
		insert into achizitii (apartament_id, bun_id, data_achizitie, cantitate, pret)
		values (@apartament_id, @bun_id, @data_achizitie, @cantitate, @pret)
	end
end

exec upsert_achizitii 1, 1, '2024-01-01', 2, 100
exec upsert_achizitii 2, 2, '2024-02-02', 3, 200
exec upsert_achizitii 2, 1, '2024-03-03', 5, 80

exec upsert_achizitii 1, 1, '2024-01-01', 2, 10000



go
create function max_chirie()
returns table
as
return
(
	select top 1 C.nume as Nume, C.prenume as Prenume, MAX(Ch.valoare) as ValoareChirie from
	clienti C
	INNER JOIN chirii Ch on C.id = Ch.client_id
	group by C.nume, C.prenume
);

select * from max_chirie();



select c.nume, c.prenume, ch.valoare
from clienti c
join chirii ch ON c.id = ch.client_id
