-- 创建数据库
create DATABASE db_man;

-- 用户信息表
CREATE TABLE `user_info` (
  `id` int NOT NULL AUTO_INCREMENT COMMENT 'id',
  `user` varchar(255) NOT NULL COMMENT '用户名',
  `pwd` varchar(255) NOT NULL COMMENT '密码',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


-- 设备表
CREATE TABLE `device_list` (
  `id` int NOT NULL COMMENT '电器id',
  `name` varchar(255) DEFAULT NULL COMMENT '电器名',
  `voltage` int DEFAULT NULL COMMENT '电压',
  `power` int DEFAULT NULL COMMENT '功率',
  `state` int DEFAULT NULL COMMENT '状态 0-关闭 1-打开',
  `dispatch` varchar(255) DEFAULT NULL COMMENT '可调度时间',
  `suggest_mod1` varchar(255) DEFAULT NULL COMMENT '节省电费',
  `suggest_mod2` varchar(255) DEFAULT NULL COMMENT '综合优化',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- 用电历史表
CREATE TABLE `history` (
  `index` int NOT NULL,
  `device_id` int NOT NULL COMMENT '设备id',
  `time_str` varchar(128) NOT NULL COMMENT '时间',
  `ele_c` int NOT NULL COMMENT '用电量',
  `money` int NOT NULL COMMENT '电费',
  PRIMARY KEY (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;