drop database if exists aod_system;

create database if not exists aod_system;

use aod_system;

create table if not exists tb_video(
id int primary key auto_increment comment '视频ID',
name varchar(32) comment '视频名称',
info text comment '视频描述',
video varchar(256) comment '视频文件url,加上静态资源根目录就是实际存储路径',
image varchar(256) comment '封面图片文件url,加上静态资源根目录就是实际存储路径'
);