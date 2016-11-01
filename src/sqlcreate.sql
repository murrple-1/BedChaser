INSERT INTO "regions" (`name`) VALUES
	('Renfrew County'),
	('North Lanark/North Grenville'),
	('Ottawa West'),
	('Ottawa Center'),
	('Ottawa East'),
	('Eastern Counties');

INSERT INTO "facilities" (`name`, `x`, `y`, `number_of_acute_care_beds`, `number_of_complex_continuing_care_beds`, `number_of_long_term_care_beds`, `regions_id`) VALUES
	('POgl9xd', 15, 40, 3, 6, 22, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa East')),
	('PN7yNViXm9uz6aUoh', 41, 41, 13, 13, 14, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa Center')),
	('z8cSLTfdz', 9, 17, 1, 15, 7, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa Center')),
	('XcaXSa0L1', 11, 22, 14, 2, 20, (SELECT `id` FROM "regions" WHERE `name` = 'North Lanark/North Grenville')),
	('Sbogl2j6zcN1j', 20, 19, 9, 7, 7, (SELECT `id` FROM "regions" WHERE `name` = 'Eastern Counties')),
	('nakSbnhwNRwV8ajZSo', 20, 0, 4, 29, 17, (SELECT `id` FROM "regions" WHERE `name` = 'Eastern Counties')),
	('KWdZ5dh',22, 25, 13, 27, 23, (SELECT `id` FROM "regions" WHERE `name` = 'North Lanark/North Grenville')),
	('qO39QYLMb', 29, 35, 5, 16, 6, (SELECT `id` FROM "regions" WHERE `name` = 'Renfrew County')),
	('h3KggWvcoLeX9M1Rfv', 20, 26, 3, 2, 25, (SELECT `id` FROM "regions" WHERE `name` = 'Renfrew County')),
	('N5fXwbNlTnjr9r0kf', 1, 10, 6, 15, 4, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa Center')),
	('139mM9O', 1, 19, 4, 19, 12, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa East')),
	('pLORXRYZ1g', 29, 34, 1, 19, 0, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa East')),
	('XMjKUWec5pWtPg', 45, 38, 15, 11, 11, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa West')),
	('jdfZtyXgvl', 1, 0, 15, 1, 12, (SELECT `id` FROM "regions" WHERE `name` = 'Ottawa Center')),
	('PoZ3ojc', 13, 5, 6, 29, 15, (SELECT `id` FROM "regions" WHERE `name` = 'Eastern Counties'));
