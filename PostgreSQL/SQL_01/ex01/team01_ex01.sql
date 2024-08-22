insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

SELECT
name,
lastname,
currency_name,
CAST(money * rate_to_usd as float) AS currency_in_usd
FROM 
(
SELECT
	COALESCE("user".name, 'not defined') AS name,
	COALESCE("user".lastname, 'not defined') AS lastname,
	currency.name AS currency_name,
	money,
	COALESCE (
		(
		SELECT rate_to_usd AS t1
		FROM currency WHERE id = balance.currency_id AND updated < balance.updated 
		ORDER BY updated DESC LIMIT 1),
			(SELECT rate_to_usd AS t2
			FROM currency WHERE id = balance.currency_id AND updated > balance.updated 
			ORDER BY updated ASC LIMIT 1)
			) AS rate_to_usd
			FROM balance
		
INNER JOIN
	(SELECT
	id,
	name
	FROM currency
	GROUP BY id, name) AS currency
ON currency.id = balance.currency_id 
		
LEFT JOIN "user"
ON "user".id = balance.user_id)
ORDER BY name DESC, lastname, currency_name;


