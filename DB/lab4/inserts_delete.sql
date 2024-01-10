CREATE PROCEDURE insert_test_category
@NoOfRows INT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @name VARCHAR(50) = 'test_category_name';
	DECLARE @n INT = 0;

	WHILE @n < @NoOfRows
	BEGIN
		INSERT INTO category(name)
		VALUES(@name);

		SET @n = @n + 1;
	END
	PRINT 'S-au inserat ' + CONVERT(VARCHAR(10), @NoOfRows) + ' valori in category.';
END

GO
CREATE PROCEDURE insert_test_product
@NoOfRows INT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @name VARCHAR(50) = 'test_product_name';
	DECLARE @created_date DATE = '2020-01-01';
	DECLARE @price MONEY = 0;
	DECLARE @seller_id BIGINT = (Select TOP 1 seller.id from seller);  
	DECLARE @category_id BIGINT = (Select TOP 1 category.id from category);  


	DECLARE @n INT = 0;

	WHILE @n < @NoOfRows
	BEGIN
		INSERT INTO product(name, created_date, seller_id, category_id, price)
		VALUES (@name, @created_date, @seller_id, @category_id, @price);
		SET @n = @n + 1;
	END

	PRINT 'S-au inserat ' + CONVERT(VARCHAR(10), @NoOfRows) + ' valori in product.';
END

GO
CREATE PROCEDURE insert_test_sale
@NoOfRows INT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @buyer_id BIGINT = (Select TOP 1 buyer.id from buyer); 
	DECLARE @product_id BIGINT = (Select TOP 1 product.id from product); 
	DECLARE @transaction_date DATETIME;
	DECLARE @transporter_id BIGINT = (Select TOP 1 transporter.id FROM transporter);
		
	DECLARE @n INT = 0;
	
	WHILE (@n < @NoOfRows)
	BEGIN
		set @transaction_date = DATEADD(day, -@n, DATEADD(year, -3, GETDATE()));
		INSERT INTO sale(buyer_id, product_id, transaction_date, transporter_id)
		VALUES(@buyer_id, @product_id, @transaction_date, @transporter_id)
		
		SET @n = @n + 1;
	END

	PRINT 'S-au inserat ' + CONVERT(VARCHAR(10), @n) + ' valori in sale';
END





GO
CREATE PROCEDURE delete_test_category
AS
BEGIN
	SET NOCOUNT ON;
	DELETE FROM category
	WHERE category.name = 'test_category_name';
	PRINT 'S-au sters ' + CONVERT(VARCHAR(10), @@ROWCOUNT) + ' valori din category.';
END

GO
CREATE PROCEDURE delete_test_product
AS
BEGIN
	SET NOCOUNT ON;
	DELETE FROM product
	WHERE product.name = 'test_product_name';
	PRINT 'S-au sters ' + CONVERT(VARCHAR(10), @@ROWCOUNT) + ' valori din product.';
END


GO
CREATE PROCEDURE delete_test_sale
AS
BEGIN
	SET NOCOUNT ON;
	DELETE FROM sale
	WHERE YEAR(sale.transaction_date) <= 2020;
	PRINT 'S-au sters ' + CONVERT(VARCHAR(10), @@ROWCOUNT) + ' valori din sale.';
END



GO
CREATE PROCEDURE run_test
@idTest INT
AS
BEGIN
	DECLARE @tableID INT = (SELECT TestTables.TableID FROM TestTables WHERE TestTables.TestID = @idTest);
	DECLARE @tableName VARCHAR(50) = (select Tables.Name From Tables where Tables.TableID = @tableID);
	DECLARE @NoOfRows INT = (SELECT TestTables.NoOfRows FROM TestTables WHERE TestTables.TestID = @idTest);
	DECLARE @ViewID INT = (SELECT TestViews.ViewID FROM TestViews WHERE TestViews.TestID = @idTest);
	DECLARE @viewName VARCHAR(50) = (select Views.Name From Views where Views.ViewID = @ViewID);
	DECLARE @testName VARCHAR(50) = (select Tests.Name from Tests where Tests.TestID = @idTest);

	DECLARE @startTime DATETIME;
	DECLARE @interTime DATETIME;
	DECLARE @endTime DATETIME;

	SET @startTime = GETDATE();
	
	DECLARE @procedura VARCHAR(50);
	SET @procedura = 'insert_test_' + @tableName;
	EXECUTE @procedura @NoOfRows;
	SET @procedura = 'delete_test_' + @tableName;
	EXECUTE @procedura;

	SET @interTime = GETDATE();
	
	EXECUTE('SELECT * FROM ' + @viewName);

	SET @endTime = GETDATE();

	INSERT INTO TestRuns VALUES (@testName, @startTime, @endTime);
	DECLARE @testRunID INT = 
		(SELECT TOP 1 T.TestRunID FROM TestRuns T
		WHERE T.Description = @testName
		ORDER BY T.TestRunID DESC);
	
	INSERT INTO TestRunTables VALUES (@testRunID, @tableID, @startTime, @interTime);
	INSERT INTO TestRunViews VALUES (@testRunID, @viewID, @interTime, @endTime);

	PRINT CHAR(10) + '---> TEST COMPLETAT CU SUCCES IN ' + 
		 CONVERT(VARCHAR(10), DATEDIFF(millisecond, @startTime, @endTime)) +
		 ' milisecunde. <---'
END

GO

