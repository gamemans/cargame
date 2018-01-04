#include "CMysqlManager.h"
#include "string.h"
CMysqlManager::CMysqlManager() {
	printf("mysql====>\n");
}

CMysqlManager::~CMysqlManager() {
}

int CMysqlManager::ReConnMysql() {
	if (mysql_real_connect(&mysql, m_strHost.c_str(), m_strUser.c_str(),
			m_strPwd.c_str(), m_strDb.c_str(), m_nPort, NULL, 0) == NULL) {
		return 0;
	}

	if (mysql_set_character_set(&mysql, m_strCharset.c_str()) != 0) {
		return 3;
	}

	return 1;
}
//初始化数据
int CMysqlManager::ConnMySQL(const char *host, unsigned int nport,
		const char * Db, const char * user, const char* passwd,
		const char * charset) {

	m_nPort = nport;

	if (host)
		m_strHost = host;
	if (Db)
		m_strDb = Db;
	if (user)
		m_strUser = user;
	if (passwd)
		m_strPwd = passwd;
	if (charset)
		m_strCharset = charset;
	else
		m_strCharset = "utf8";

	if (mysql_init(&mysql) == NULL) {
		return 1;
	}

	if (mysql_real_connect(&mysql, host, user, passwd, Db, nport, NULL,
			0) == NULL) {
		return 2;
	}

	if (mysql_set_character_set(&mysql, m_strCharset.c_str()) != 0) {
		return 3;
	}

	printf("libmysql---\n");

	return 0;
}

//查询数据
string CMysqlManager::SelectData(const char * SQL, int Cnum,
		const char * fieldspilt, const char * rowspilt, int &recordnum) {
	MYSQL_ROW m_row;
	MYSQL_RES *m_res;
	char sql[2048];
	sprintf(sql, "%s", SQL);

	int err = mysql_ping(&mysql);
	if (err != 0) {
		ReConnMysql();
	}

	printf("%s\n", sql);
	recordnum = 0;

	if (mysql_query(&mysql, SQL) != 0) {
		return "";
	}
	m_res = mysql_store_result(&mysql);

	if (m_res == NULL) {
		return "";
	}
	string str("");
	while ((m_row = mysql_fetch_row(m_res))) {
		for (int i = 0; i < Cnum; i++) {
			if(m_row[i])
			{
				str += m_row[i];
			}
			str += fieldspilt;
		}

		str = str.substr(0, str.length() - 1);

		str += rowspilt;
		recordnum++;
	}

	if (recordnum > 0) {
		str = str.substr(0, str.length() - 1);
	}

	mysql_free_result(m_res);

	printf("%s\n", str.c_str());
	return str;
}

//插入数据
int CMysqlManager::InsertData(char * SQL) {
	char sql[2048];
	sprintf(sql, "%s", SQL);

	int err = mysql_ping(&mysql);
	if (err != 0) {
		ReConnMysql();
	}

	if (mysql_real_query(&mysql, sql, strlen(sql)) != 0) {
		return 0;
	}
	return 1;
}

//更新数据
int CMysqlManager::UpdateData(char * SQL) {
	char sql[2048];
	sprintf(sql, "%s", SQL);

	int err = mysql_ping(&mysql);
	if (err != 0) {
		ReConnMysql();
	}

	if (mysql_real_query(&mysql, sql, strlen(sql)) != 0) {
		return 1;
	}
	return 0;
}

//删除数据
int CMysqlManager::DeleteData(char * SQL) {
	char sql[2048];
	sprintf(sql, "%s", SQL);

	int err = mysql_ping(&mysql);
	if (err != 0) {
		ReConnMysql();
	}

	if (mysql_real_query(&mysql, sql, strlen(sql)) != 0) {
		return 1;
	}
	return 0;
}

//关闭数据库连接
void CMysqlManager::CloseMySQLConn() {
	mysql_close(&mysql);
}
