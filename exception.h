#pragma once
class Exception {};
class InvalidInputException : public Exception {};
class IndexOutOfBoundsException : public Exception {};
class EmptyListException : public Exception {};
class ItemNotFound : public Exception {};
class VertexNotAdded : public Exception {};
