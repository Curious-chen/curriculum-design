from elasticsearch import Elasticsearch
import json

es = Elasticsearch([{'host': '127.0.0.1', 'port': 9200}])


def put():
    pass


def delete():
    pass


def query():
    print(es.get(index='movies', doc_type='movie', id='2'))

    # 匹配所有输出
    body = {
        "query": {
            "match_all": {}
        }
    }
    # print(json.dumps(es.search(body=body), sort_keys=True, indent=2))

    # 查询字符串
    body = {
        "query": {
            "query_string": {
                "query": "Ford"
            }
        }
    }

    # 过滤查询
    body = {
        "query": {
            "bool": {
                "must": {
                    "query_string": {
                        'query': 'Lawrence'
                    }
                },
                "filter": {
                    "term": {"year": 1962},
                }
            }
        }
    }
    print(json.dumps(es.search(body=body), indent=2))


if __name__ == '__main__':
    query()
