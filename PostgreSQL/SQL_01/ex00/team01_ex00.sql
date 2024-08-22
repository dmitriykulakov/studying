SELECT 
	COALESCE(name, 'not defined') AS name,
	COALESCE(lastname, 'not defined') AS lastname,
	type, volume, 
	COALESCE (currency_name, 'not defined') AS currency_name,
	last_rate_to_usd,
	CAST(last_rate_to_usd * volume as float) as total_volume_in_usd
	FROM (SELECT "user".name as name, "user".lastname as lastname, 
		balance.type as type, SUM(balance.money) as volume, currency_name, 
		COALESCE (last_rate_to_usd, 1) AS last_rate_to_usd
		FROM balance 
		LEFT JOIN "user"
		ON "user".id = balance.user_id
		LEFT JOIN (SELECT currency.id as currency_id_tmp, currency.name as currency_name,
			currency.rate_to_usd as last_rate_to_usd
			FROM (SELECT id, MAX(updated) as updated FROM currency
			GROUP BY id) as last_update, currency
			WHERE currency.id = last_update.id AND currency.updated = last_update.updated)
		ON currency_id = currency_id_tmp
	GROUP BY "user".name, "user".lastname, balance.type, currency_name, last_rate_to_usd)
ORDER BY name DESC, lastname ASC, type ASC

