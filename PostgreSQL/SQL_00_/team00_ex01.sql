SELECT total_cost, '{' || tour || '}' as tour
	FROM v_travel_way
WHERE total_cost = (SELECT MIN(total_cost) FROM v_travel_way) OR total_cost = (SELECT MAX(total_cost) FROM v_travel_way)
ORDER BY total_cost, tour





	
	