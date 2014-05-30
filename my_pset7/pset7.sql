--
-- Database: `pset7`
--

CREATE DATABASE IF NOT EXISTS  `pset7`;


--
-- Table structure for table `users`
--


CREATE TABLE `users` (
 `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
 `username` varchar(255) NOT NULL,
 `hash` varchar(255) NOT NULL,
 `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
 `email` varchar(100) DEFAULT NULL,
 PRIMARY KEY (`id`),
 UNIQUE KEY `username` (`username`),
 UNIQUE KEY `username_2` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;


--
-- Dumping data for table `pset7`.`users`
--

INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(1, 'caesar', '$1$50$GHABNWBNE/o4VL7QjmQ6x0');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(2, 'hirschhorn', '$1$50$lJS9HiGK6sphej8c4bnbX.');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(3, 'jharvard', '$1$50$RX3wnAMNrGIbgzbRYrxM1/');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(4, 'malan', '$1$HA$azTGIMVlmPi9W9Y12cYSj/');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(5, 'milo', '$1$HA$6DHumQaK4GhpX8QE23C8V1');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(6, 'skroob', '$1$50$euBi4ugiJmbpIbvTTfmfI.');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(7, 'zamyla', '$1$50$uwfqB45ANW.9.6qaQ.DcF.');



--
-- Table portfolio
--

CREATE TABLE IF NOT EXISTS `pset7`.`portfolio`(

	`id` int(10)  unsigned NOT NULL,
	`symbol` varchar(12) NOT NULL,
	`shares` int(20) NOT NULL,
	PRIMARY KEY (`id`,`symbol`)

)ENGINE=InnoDB AUTO_INCREMENT=8;



--
--	Table History
--

CREATE TABLE IF NOT EXISTS  `pset7`.`history` (
 `transation_id` int(10)  unsigned NOT NULL AUTO_INCREMENT,
 `id` int(11) unsigned NOT NULL,
 `transaction_type` varchar(10) NOT NULL,
 `company` varchar(255) NOT NULL,
 `symbol` varchar(15) NOT NULL,
 `shares` int(100) unsigned NOT NULL,
 `price` decimal(65,4) unsigned NOT NULL,
 `time_stamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
 PRIMARY KEY (`transation_id`)
) ENGINE=InnoDB;

