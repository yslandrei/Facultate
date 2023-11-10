use ebay_db_manual
go

--toti angajatii care au adresa in orasul Cluj-Napoca
select * from employee
join address on employee.address_id=address.id
where address.city='Cluj-Napoca';

--toate produsele care au pretul mai mare decat 1000 si al caror vanzatori sunt din Romania
select * from seller
join address on seller.address_id=address.id
join product on product.seller_id=seller.id
where product.price > 1000 and address.country='Romania';

--toate vanzarile de produse din categoria Furniture 
select * from product
join category on category.id=product.category_id
join sale on sale.product_id=product.id
where category.name='Furniture';

--toate vanzarile de produse care au fost livrate cu un transportator ce are pretul per kilometru mai mic ca 0.10
select product.seller_id, product.name, transporter.name, transporter.price_per_km, sale.transaction_date
from product 
join sale on sale.product_id=product.id
join transporter on transporter.id=sale.transporter_id
where transporter.price_per_km < 0.10;

--toti cumparatorii care au cumparat ceva inainte de data 2023.10.01 si sunt din Romania
select * from buyer
join address on buyer.address_id=address.id
join sale on sale.buyer_id=buyer.id
where sale.transaction_date < '2023-10-01' and address.country='Romania';

--toate categoriile ce au mai mult de un produs listat vandut
SELECT category.name, COUNT(category.id) as num_products
FROM category
JOIN product ON category.id = product.category_id
JOIN sale ON sale.product_id = product.id
GROUP BY category.name
having COUNT(category.id) > 1;

--cati angajati programatori separati are fiecare oras
SELECT address.city, COUNT(employee.id) as num_employees
FROM employee
JOIN address ON employee.address_id = address.id
JOIN employee_department ON employee.id = employee_department.employee_id
JOIN department on employee_department.department_id=department.id
WHERE department.name='Software Development'
GROUP BY address.city;

--cati angajati din cluj napoca lucreaza pe fiecare tip de contract (full time, part time, 6 ore)
SELECT hours_per_day, COUNT(employee.id) as num_employees
FROM employee
JOIN address ON employee.address_id = address.id
JOIN employee_department ON employee.id = employee_department.employee_id
WHERE address.city='Cluj-Napoca'
GROUP BY hours_per_day
having COUNT(employee.id) > 1;

--produsele distincte cumparate de fiecare user dupa date de 2023.10.01
select distinct product.seller_id, product.name, buyer.name, sale.transaction_date
from product 
join sale on sale.product_id=product.id
join buyer on buyer.id=sale.buyer_id
where transaction_date > '2023-10-01';

--toti angajatii distincti ce nu au functii in Customer Service
select distinct employee.name, employee.id, employee.salary from employee
join employee_department on employee_department.employee_id=employee.id
join department on department.id=employee_department.department_id
where department.name!='Customer Service';
