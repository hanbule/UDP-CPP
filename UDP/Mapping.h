#pragma once
#include <map>
#include <string>

using namespace std;

struct CM {
	char* name;
	map<char*, Mem> fields;
	map<char*, Mem> methods;

	CM(char* clsName) : name(clsName) {}
};

struct Mem {
	char* name;
	char* desc;
	bool isStatic;

	Mem(char* memName, char* memDesc, bool stat) : name(memName), desc(memDesc), isStatic(stat) {}
};

class Mapping
{
public:
	static map<char*, CM> lookup;
	
	Mapping() {
		setup();
	}

	static CM getClass(const char* key) {
		return lookup.at((char*)key);
	}

	static const char* getClassName(const char* key) {
		return getClass(key).name;
	}

private:
	// Setup lookup map
	static void setup() {
		// base - normal jvm classes
		CM m = make("List", "java/util/List");
		method(m, "get", "(I)Ljava/lang/Object;", false);
		method(m, "toArray", "()[Ljava/lang/Object;", false);
		method(m, "size", "()I", false);
		m = make("Set", "java/util/Set");
		method(m, "toArray", "()[Ljava/lang/Object;", false);
		method(m, "size", "()I", false);
		// obfuscated minecraft classes - 1.12
		m = make("Entity", "ve");
		field(m, "x", "p", "D", false);
		field(m, "y", "q", "D", false);
		field(m, "z", "r", "D", false);
		method(m, "getID", "S", "()I", false);
		method(m, "getName", "h_", "()Ljava/lang/String;", false);
		m = make("WorldClient", "brz");
		field(m, "entities", "K", "Ljava/util/Set;", false);
		method(m, "setTime", "b", "(J)V", false);
		m = make("PlayerSP", "bub");
		field(m, "x", "p", "D", false);
		field(m, "y", "q", "D", false);
		field(m, "z", "r", "D", false);
		field(m, "yaw", "v", "F", false);
		field(m, "pitch", "w", "F", false);
		method(m, "getID", "S", "()I", false);
		method(m, "getName", "h_", "()Ljava/lang/String;", false);
		method(m, "setSprint", "f", "(Z)V", false);
		m = make("Minecraft", "bhz");
		field(m, "player", "h", "Lbub;", false);
		field(m, "world", "f", "Lbrz;", false);
		method(m, "getMinecraft", "z", "()Lbhz;", true);
	}

	static void field(CM cm, char* name, char* desc, bool isStatic) {
		field(cm, name, name, desc, isStatic);
	}

	static void method(CM cm, char* name, char* desc, bool isStatic) {
		method(cm, name, name, desc, isStatic);
	}

	static void field(CM cm, char* keyName, char* obName, char* desc, bool isStatic) {
		cm.fields[keyName] = Mem(obName, desc, isStatic);
	}

	static void method(CM cm, char* keyName, char* obName, char* desc, bool isStatic) {
		cm.methods[keyName] = Mem(obName, desc, isStatic);
	}

	static CM make(char* key, char* name) {
		CM cm = CM(name);
		lookup[key] = cm;
		return cm;
	}
};