#include <iostream>
#include <iterator>
#include <boost/scoped_ptr.hpp>
#include <boost/locale/encoding.hpp>
#include <soci.h>
#include <soci-mysql.h>

std::string gbk2utf8(std::string gbk)
{
	return boost::locale::conv::between(gbk, "utf-8", "gbk");
}
std::string utf82gbk(std::string utf8)
{
	return boost::locale::conv::between(utf8, "gbk", "utf-8");
}

int main()
{
	std::cout << "mysql_soci_demo" << std::endl;

	int connection_pool_size = 10;
	std::string connect_string = "db=data user=root password=ry317107 charset=utf8";
	const soci::backend_factory& backend_factory = *soci::factory_mysql();
	boost::scoped_ptr<soci::connection_pool> pool;

	//连接mysql
	try
	{
		pool.reset(new soci::connection_pool(connection_pool_size));
		for (size_t i = 0; i != connection_pool_size; i++)
		{
			soci::session& sql = pool->at(i);
			sql.open(backend_factory, connect_string);
		}
	}
	catch (const soci::soci_error& e)
	{
		std::cout << " soci::soci_error :" <<  e.what()  << std::endl;
	}

	//查询所有
	std::cout << " mysql connect succeed !" << std::endl;
	std::cout << " SELECT * FROM tb_user... !" << std::endl;
	try
	{
		soci::session sql(*pool);
		std::string sql_statement = "SELECT * FROM tb_user;";

		for (; true; )
		{
			try
			{
				soci::transaction t(sql);
				soci::rowset<> rs(sql.prepare << sql_statement);
				t.commit();
				for (soci::rowset<>::iterator it = rs.begin(); it != rs.end(); ++it)
				{
					std::string id = utf82gbk(it->get<std::string>(0, ""));
				}
				break;
			}
			catch (const soci::mysql_soci_error& e)
			{
				if (e.err_num_ == 1213)
				{
					continue;
				}
				throw e;
			}
			catch (const soci::soci_error&)
			{
				sql.reconnect();
				continue;
			}
		}
	}
	catch (const soci::soci_error& e)
	{
		std::cout << " soci::soci_error :" << e.what() << std::endl;
	}
	std::cout << " SELECT * FROM tb_user succeed !" << std::endl;

	//插入INSERT INTO `data`.`tb_user` (`id`, `name`, `pass`) VALUES ('456', 'dengye', 'dengye');
	std::cout << "INSERT INTO ... !" << std::endl;
	try
	{
		soci::session sql(*pool);
		std::string sql_statement =
			"INSERT INTO tb_user VALUES("
			":id	,"
			":name	,"
			":pass	);"
			;
		std::string id = "456";
		std::string	name = "dengye";
		std::string	pass = "dengye";
		for (; true;)
		{
			try
			{
				soci::transaction t(sql);
				sql << sql_statement, soci::use(id), soci::use(name), soci::use(pass);
				t.commit();
				break;
			}
			catch (const soci::mysql_soci_error& e)
			{
				if (e.err_num_ == 1213)
				{
					continue;
				}
				throw e;
			}
			catch (const soci::soci_error&)
			{
				sql.reconnect();
				continue;
			}
		}
	}
	catch (const soci::soci_error& e)
	{
		std::cout << " soci::soci_error :" << e.what() << std::endl;
	}
	std::cout << " INSERT INTO succeed !" << std::endl;

	//更新UPDATE `data`.`tb_user` (`id`, `name`, `pass`) VALUES ('456', 'dengye', '107');
	std::cout << "UPDATE ... !" << std::endl;
	try
	{
		soci::session sql(*pool);
		std::string sql_statement =
			"UPDATE tb_user SET "
			"name		= :name,"
			"pass		= :pass "
			"WHERE id	= :id ;"
			;
		std::string id = "456";
		std::string	name = "dengye";
		std::string	pass = "dengye";
		for (; true;)
		{
			try
			{
				soci::transaction t(sql);
				sql << sql_statement, soci::use(name), soci::use(pass), soci::use(id);
				t.commit();
				break;
			}
			catch (const soci::mysql_soci_error& e)
			{
				if (e.err_num_ == 1213)
				{
					continue;
				}
				throw e;
			}
			catch (const soci::soci_error&)
			{
				sql.reconnect();
				continue;
			}
		}
	}
	catch (const soci::soci_error& e)
	{
		std::cout << " soci::soci_error :" << e.what() << std::endl;
	}
	std::cout << " UPDATE succeed !" << std::endl;

	//条件查询
	std::cout << "SELECT ... !" << std::endl;
	try
	{
		soci::session sql(*pool);
		std::string sql_statement =
			"SELECT * FROM tb_user WHERE name = :name;"
			;

		std::string	name = "dengye";
		for (; true;)
		{
			try
			{
				soci::transaction t(sql);
				soci::rowset<> rs((sql.prepare << sql_statement, soci::use(name)));
				t.commit();
				soci::rowset<>::iterator it = rs.begin();
				if (it != rs.end())
				{
					std::string id = utf82gbk(it->get<std::string>(0, ""));
				}
				break;
			}
			catch (const soci::mysql_soci_error& e)
			{
				if (e.err_num_ == 1213)
				{
					continue;
				}
				throw e;
			}
			catch (const soci::soci_error&)
			{
				sql.reconnect();
				continue;
			}
		}
	}
	catch (const soci::soci_error& e)
	{
		std::cout << " soci::soci_error :" << e.what() << std::endl;
	}
	std::cout << " SELECT succeed !" << std::endl;

	//条件删除
	std::cout << "DELETE ... !" << std::endl;
	try
	{
		soci::session sql(*pool);
		std::string sql_statement =
			"DELETE FROM tb_user WHERE id = :id;"
			;

		std::string	id = "456";
		for (; true;)
		{
			try
			{
				soci::transaction t(sql);
				sql << sql_statement, soci::use(id);
				t.commit();
				break;
			}
			catch (const soci::mysql_soci_error& e)
			{
				if (e.err_num_ == 1213)
				{
					continue;
				}
				throw e;
			}
			catch (const soci::soci_error&)
			{
				sql.reconnect();
				continue;
			}
		}
	}
	catch (const soci::soci_error& e)
	{
		std::cout << " soci::soci_error :" << e.what() << std::endl;
	}
	std::cout << " DELETE succeed !" << std::endl;

	return 0;
}