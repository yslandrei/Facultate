USE ebay_db_2;

CREATE TABLE log_table 
(
	id INT PRIMARY KEY IDENTITY,
	operation_type VARCHAR(20),
	table_name VARCHAR(20),
	execution_time DATETIME,
)
GO

CREATE FUNCTION validate_parameters_employee(@name VARCHAR(50), @salary MONEY, @hours_per_day INT)
RETURNS VARCHAR(200)
AS
BEGIN
	DECLARE @error VARCHAR(200)
	SET @error = ''

	IF (@name = '')
		SET @error = @error + 'Name cannot be empty'

	IF (@salary < 0) 
		SET @error = @error + 'The salary cannot be negative'

	IF (@hours_per_day < 0) 
		SET @error = @error + 'The hours per day cannot be negative'

	RETURN @error
END
GO


CREATE FUNCTION validate_parameters_department(@name VARCHAR(50))
RETURNS VARCHAR(200)
AS
BEGIN
	DECLARE @error VARCHAR(200)
	SET @error = ''

	IF (@name = '')
		SET @error = @error + 'Name cannot be empty'

	RETURN @error
END
GO


CREATE FUNCTION validate_parameters_employee_department(@starting_date DATETIME)
RETURNS VARCHAR(200)
AS
BEGIN
	DECLARE @error VARCHAR(200)
	SET @error = ''

	IF (@starting_date < '2000-01-01') 
		SET @error = @error + 'The starting date cannot be before the company creation'

	RETURN @error
END
GO

CREATE PROCEDURE insert_into_tables(@name VARCHAR(50), @salary MONEY, @hours_per_day INT, @department_name VARCHAR(50), @starting_date DATETIME)
AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		DECLARE @error_msg VARCHAR(200)
		SET @error_msg = dbo.validate_parameters_employee(@name, @salary, @hours_per_day)
		IF (@error_msg <> '')
		BEGIN
			PRINT @error_msg
			RAISERROR(@error_msg, 14, 1)
		END
		
		
		INSERT INTO employee VALUES (@name, @salary, @hours_per_day)
		INSERT INTO log_table VALUES ('INSERT', 'employee', CURRENT_TIMESTAMP)

		SET @error_msg = dbo.validate_parameters_department(@department_name)
		IF (@error_msg <> '')
		BEGIN
			PRINT @error_msg
			RAISERROR(@error_msg, 14, 1)
		END

		INSERT INTO department VALUES (@department_name)
		INSERT INTO log_table VALUES ('INSERT', 'department', CURRENT_TIMESTAMP)
		
		SET @error_msg = dbo.validate_parameters_employee_department(@starting_date)
		DECLARE @employee_id INT, @department_id INT
		SET @employee_id = (SELECT MAX(id) FROM employee)
		SET @department_id = (SELECT MAX(id) FROM department)

		IF (@error_msg <> '')
		BEGIN
			PRINT @error_msg
			RAISERROR(@error_msg, 14, 1)
		END

		INSERT INTO employee_department VALUES (@employee_id, @department_id, @starting_date)
		INSERT INTO log_table VALUES ('INSERT', 'Boardings', CURRENT_TIMESTAMP)

		COMMIT TRAN
		PRINT 'Transaction commited'
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		ROLLBACK TRAN
		PRINT 'Transaction rollbacked'
	END CATCH
END



EXEC dbo.insert_into_tables 'test', 5000, 8, 'test_dep', '2024-01-01';

EXEC dbo.insert_into_tables 'test', 5000, 8, 'test_dep', '1999-01-01';
EXEC dbo.insert_into_tables '', 5000, 8, 'test_dep', '2024-01-01';
EXEC dbo.insert_into_tables 'test', 5000, -8, 'test_dep', '2024-01-01';

select * from log_table
select * from employee
select * from department
select * from employee_department
go

CREATE PROCEDURE insert_into_tables2(@name VARCHAR(50), @salary MONEY, @hours_per_day INT, @department_name VARCHAR(50), @starting_date DATETIME)
AS
BEGIN
	DECLARE @err BIT
	SET @err = 0

	BEGIN TRAN
	BEGIN TRY
		DECLARE @error_msg VARCHAR(200)
		SET @error_msg = dbo.validate_parameters_employee(@name, @salary, @hours_per_day)
		IF (@error_msg <> '')
		BEGIN
			PRINT @error_msg
			RAISERROR(@error_msg, 14, 1)
		END
		
		INSERT INTO employee VALUES (@name, @salary, @hours_per_day)
		INSERT INTO log_table VALUES ('INSERT', 'employee', CURRENT_TIMESTAMP)

		COMMIT TRAN
		PRINT 'Transaction commited'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		INSERT log_table VALUES ('INSERT ERROR', 'employee', CURRENT_TIMESTAMP)
		PRINT 'Transaction rollbacked'
		SET @err = 1
	END CATCH

	BEGIN TRAN
	BEGIN TRY
		SET @error_msg = dbo.validate_parameters_department(@department_name)
		IF (@error_msg <> '')
		BEGIN
			PRINT @error_msg
			RAISERROR(@error_msg, 14, 1)
		END

		INSERT INTO department VALUES (@department_name)
		INSERT INTO log_table VALUES ('INSERT', 'department', CURRENT_TIMESTAMP)

		COMMIT TRAN
		PRINT 'Transaction commited'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		INSERT log_table VALUES ('INSERT ERROR', 'department', CURRENT_TIMESTAMP)
		PRINT 'Transaction rollbacked'
		SET @err = 1
	END CATCH

	IF (@err = 1)
		return

	BEGIN TRAN
	BEGIN TRY
		SET @error_msg = dbo.validate_parameters_employee_department(@starting_date)
		DECLARE @employee_id INT, @department_id INT
		SET @employee_id = (SELECT MAX(id) FROM employee)
		SET @department_id = (SELECT MAX(id) FROM department)

		IF (@error_msg <> '')
		BEGIN
			PRINT @error_msg
			RAISERROR(@error_msg, 14, 1)
		END

		INSERT INTO employee_department VALUES (@employee_id, @department_id, @starting_date)
		INSERT INTO log_table VALUES ('INSERT', 'employee_department', CURRENT_TIMESTAMP)

		COMMIT TRAN
		PRINT 'Transaction commited'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		INSERT log_table VALUES ('INSERT ERROR', 'employee_department', CURRENT_TIMESTAMP)
		PRINT 'Transaction rollbacked'
	END CATCH
END


EXEC dbo.insert_into_tables2 'test', 5000, 8, 'test_dep', '2024-01-01';

EXEC dbo.insert_into_tables2 'test', 5000, 8, 'test_dep', '1999-01-01';
EXEC dbo.insert_into_tables2 '', 5000, 8, 'test_dep', '2024-01-01';

select * from log_table
select * from employee
select * from department
select * from employee_department