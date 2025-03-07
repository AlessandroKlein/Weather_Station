-- phpMyAdmin SQL Dump
-- version 4.9.0.1
-- https://www.phpmyadmin.net/
--
-- Servidor: sql205.infinityfree.com
-- Tiempo de generación: 07-03-2025 a las 08:54:08
-- Versión del servidor: 10.6.19-MariaDB
-- Versión de PHP: 7.2.22

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `if0_38462059_est`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `api`
--

CREATE TABLE `api` (
  `id` int(11) NOT NULL,
  `hash` varchar(64) NOT NULL,
  `usuario_id` int(11) NOT NULL,
  `estacion` varchar(255) NOT NULL,
  `country` varchar(100) DEFAULT NULL,
  `city` varchar(100) DEFAULT NULL,
  `state` varchar(100) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Volcado de datos para la tabla `api`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `sensor_data`
--

CREATE TABLE `sensor_data` (
  `id` int(11) NOT NULL,
  `api_id` int(11) NOT NULL,
  `windDirectionADC` int(11) NOT NULL DEFAULT 0,
  `windDirectionGradient` float NOT NULL DEFAULT 0,
  `rainTicks24h` int(11) NOT NULL DEFAULT 0,
  `rainTicks60m` int(11) NOT NULL DEFAULT 0,
  `temperatureC` float NOT NULL DEFAULT 0,
  `temperatureAHT` float NOT NULL DEFAULT 0,
  `temperatureBMP` float NOT NULL DEFAULT 0,
  `windSpeed` float NOT NULL DEFAULT 0,
  `windSpeedMax` float NOT NULL DEFAULT 0,
  `barometricPressure` float NOT NULL DEFAULT 0,
  `humidity` float NOT NULL DEFAULT 0,
  `UVIndex` float NOT NULL DEFAULT 0,
  `lux` float NOT NULL DEFAULT 0,
  `co2` float NOT NULL DEFAULT 0,
  `tvoc` float NOT NULL DEFAULT 0,
  `heatIndex` float NOT NULL DEFAULT 0,
  `windChill` float NOT NULL DEFAULT 0,
  `dewPoint` float NOT NULL DEFAULT 0,
  `aqi` int(11) NOT NULL DEFAULT 0,
  `et0` float NOT NULL DEFAULT 0,
  `altitude` float NOT NULL DEFAULT 0,
  `cloudIndex` float NOT NULL DEFAULT 0,
  `windSpeedAvg` float NOT NULL DEFAULT 0,
  `timestamp` datetime NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Volcado de datos para la tabla `sensor_data`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `sensor_queue`
--

CREATE TABLE `sensor_queue` (
  `id` int(11) NOT NULL,
  `data` longtext DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `sent_at` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `usuarios`
--

CREATE TABLE `usuarios` (
  `id` int(11) NOT NULL,
  `username` varchar(50) NOT NULL,
  `email` varchar(100) NOT NULL,
  `password` varchar(255) NOT NULL,
  `plan` int(11) NOT NULL DEFAULT 1,
  `ip` varchar(45) DEFAULT NULL,
  `country` varchar(100) DEFAULT NULL,
  `country_code` varchar(2) DEFAULT NULL,
  `city` varchar(100) DEFAULT NULL,
  `state` varchar(100) DEFAULT NULL,
  `localtime` datetime DEFAULT NULL,
  `risk` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL
) ;

--
-- Volcado de datos para la tabla `usuarios`
--

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `api`
--
ALTER TABLE `api`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `hash` (`hash`);

--
-- Indices de la tabla `sensor_data`
--
ALTER TABLE `sensor_data`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `api`
--
ALTER TABLE `api`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT de la tabla `sensor_data`
--
ALTER TABLE `sensor_data`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT de la tabla `usuarios`
--
ALTER TABLE `usuarios`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
