-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jun 22, 2021 at 04:33 PM
-- Server version: 10.3.29-MariaDB-0+deb10u1
-- PHP Version: 7.3.27-1~deb10u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `xsmartfirekiller`
--

-- --------------------------------------------------------

--
-- Table structure for table `data_incident`
--

CREATE TABLE `data_incident` (
  `id_incident` int(11) NOT NULL,
  `date` date NOT NULL,
  `i_temperature` int(11) NOT NULL,
  `i_gaz` int(11) NOT NULL,
  `id_video` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf16 COLLATE=utf16_bin;

--
-- Dumping data for table `data_incident`
--

INSERT INTO `data_incident` (`id_incident`, `date`, `i_temperature`, `i_gaz`, `id_video`) VALUES
(1, '2021-06-22', 22, 63, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `data_sensor`
--

CREATE TABLE `data_sensor` (
  `id_data` int(11) NOT NULL,
  `date` date NOT NULL,
  `temperature` float NOT NULL,
  `gaz` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf16 COLLATE=utf16_bin;

--
-- Dumping data for table `data_sensor`
--

INSERT INTO `data_sensor` (`id_data`, `date`, `temperature`, `gaz`) VALUES
(1, '2021-06-22', 10, 50),
(2, '2021-06-22', 22, 62),
(3, '2021-06-22', 22, 62),
(4, '2021-06-22', 22, 62),
(5, '2021-06-22', 22, 62),
(6, '2021-06-22', 22, 62),
(7, '2021-06-22', 22, 62),
(8, '2021-06-22', 22, 62),
(9, '2021-06-22', 22, 62),
(10, '2021-06-22', 22, 62),
(11, '2021-06-22', 22, 63);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `data_incident`
--
ALTER TABLE `data_incident`
  ADD PRIMARY KEY (`id_incident`);

--
-- Indexes for table `data_sensor`
--
ALTER TABLE `data_sensor`
  ADD PRIMARY KEY (`id_data`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `data_incident`
--
ALTER TABLE `data_incident`
  MODIFY `id_incident` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `data_sensor`
--
ALTER TABLE `data_sensor`
  MODIFY `id_data` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
